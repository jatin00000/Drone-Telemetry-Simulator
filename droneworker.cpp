#include "DroneWorker.h"

#include <QMetaObject>

#include "Logger.h"

DroneWorker::DroneWorker(QObject *parent) : QObject(parent) {}

DroneWorker::~DroneWorker()
{

    stopSimulator();
}

void DroneWorker::startSimulator(DroneSimulator *sim)
{

    if (m_sim)
        return;

    m_sim = sim;

    // move simulator to thread and start

    sim->moveToThread(&m_thread);

    connect(&m_thread, &QThread::started, sim, &DroneSimulator::start);

    connect(&m_thread, &QThread::finished, sim, &DroneSimulator::stop);

    m_thread.start();

    Logger::instance().log("DroneWorker: thread started");
}

void DroneWorker::stopSimulator()
{

    if (!m_sim)
        return;

    // ask simulator to stop (queued call)

    QMetaObject::invokeMethod(m_sim, "stop", Qt::BlockingQueuedConnection);

    m_thread.quit();

    m_thread.wait();

    Logger::instance().log("DroneWorker: thread stopped");

    m_sim = nullptr;
}