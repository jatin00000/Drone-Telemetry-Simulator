#include "MainWindow.h"

#include "ui_MainWindow.h"

#include "SimulatorFactory.h"

#include "Logger.h"

#include <QMetaType>

#include "RandomWalkStrategy.h"

#include "HoverStrategy.h"

#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)

    : QMainWindow(parent),

      ui(new Ui::MainWindow),

      m_model(new TelemetryModel(this)),

      m_simulator(nullptr),

      m_worker(new DroneWorker(this))

{

    ui->setupUi(this);

    // set up UI controls

    ui->comboStrategy->addItem("Hover", QVariant::fromValue(StrategyType::Hover));

    ui->comboStrategy->addItem("Random Walk", QVariant::fromValue(StrategyType::RandomWalk));

    ui->btnStart->setEnabled(true);

    ui->btnStop->setEnabled(false);

    connect(ui->btnStart, &QPushButton::clicked, this, &MainWindow::onStartClicked);

    connect(ui->btnStop, &QPushButton::clicked, this, &MainWindow::onStopClicked);

    connect(ui->btnFailure, &QPushButton::toggled, this, &MainWindow::onSimulateFailureToggled);

    connect(ui->comboStrategy, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onStrategyChanged);

    // model updates UI

    connect(m_model, &TelemetryModel::telemetryUpdated, this, &MainWindow::onTelemetryUpdated);

    // logger

    connect(&Logger::instance(), &Logger::newLog, this, &MainWindow::appendLog);

    appendLog("MainWindow initialized.");
}

MainWindow::~MainWindow()
{

    if (m_worker)
    {

        m_worker->stopSimulator();
    }

    delete ui;
}

void MainWindow::onStartClicked()
{

    if (m_simulator)
        return;

    int strat = ui->comboStrategy->currentData().toInt();

    m_simulator = SimulatorFactory::createSingleDroneSimulator("DRONE-001", strat, nullptr);

    // connect simulator tick -> model

    connect(m_simulator, &DroneSimulator::simulatedTick, m_model, &TelemetryModel::updateFromSimulator, Qt::QueuedConnection);

    connect(m_simulator, &DroneSimulator::eventOccurred, [](const QString &s)
            { Logger::instance().log(s); });

    m_worker->startSimulator(m_simulator);

    ui->btnStart->setEnabled(false);

    ui->btnStop->setEnabled(true);

    appendLog("Simulator started.");
}

void MainWindow::onStopClicked()
{

    if (!m_simulator)
        return;

    m_worker->stopSimulator();

    // delete simulator object (it is parented to no one)

    m_simulator->deleteLater();

    m_simulator = nullptr;

    ui->btnStart->setEnabled(true);

    ui->btnStop->setEnabled(false);

    appendLog("Simulator stopped.");
}

void MainWindow::onSimulateFailureToggled(bool checked)
{

    if (m_simulator)
    {

        QMetaObject::invokeMethod(m_simulator, "setFailureMode", Qt::QueuedConnection, Q_ARG(bool, checked));

        appendLog(QString("Failure mode toggled: %1").arg(checked ? "ON" : "OFF"));
    }
    else
    {

        appendLog("Failure toggle changed but simulator not running.");
    }
}

void MainWindow::onStrategyChanged(int idx)
{

    // if simulator running, switch strategy dynamically

    if (!m_simulator)
        return;

    int strat = ui->comboStrategy->itemData(idx).toInt();

    // create new strategy on the heap and set by queued call

    MovementStrategy *newStr = nullptr;

    if (strat == StrategyType::RandomWalk)
    {

        newStr = new RandomWalkStrategy();
    }
    else
    {

        newStr = new HoverStrategy();
    }

    // wrap in unique_ptr via lambda in simulator thread

    QMetaObject::invokeMethod(m_simulator, [this, newStr]()
                              {
                                  std::unique_ptr<MovementStrategy> ptr(newStr);

                                  m_simulator->setStrategy(std::move(ptr));

                                  Logger::instance().log("Strategy switched in simulator."); }, Qt::QueuedConnection);
}

void MainWindow::onTelemetryUpdated()
{

    TelemetrySnapshot snap = m_model->snapshot();

    ui->lblDroneId->setText(snap.id);

    ui->lblLat->setText(QString::number(snap.latitude, 'f', 6));

    ui->lblLon->setText(QString::number(snap.longitude, 'f', 6));

    ui->lblAlt->setText(QString::number(snap.altitude, 'f', 2));

    ui->lblHeading->setText(QString::number(snap.heading, 'f', 1));

    ui->lblSpeed->setText(QString::number(snap.speed, 'f', 2));

    ui->lblBattery->setText(QString("%1%").arg(snap.battery));

    QString fix = (snap.gpsFix == TelemetrySnapshot::GpsFix::Fix3D) ? "3D" :

                  (snap.gpsFix == TelemetrySnapshot::GpsFix::Fix2D) ? "2D"
                                                                    : "No Fix";

    ui->lblGps->setText(fix);
}

void MainWindow::appendLog(const QString &entry)
{

    QString msg = QDateTime::currentDateTime().toString(Qt::ISODate) + " - " + entry;

    ui->logView->appendPlainText(msg);
}
