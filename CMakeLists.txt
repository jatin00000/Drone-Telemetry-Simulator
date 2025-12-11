cmake_minimum_required(VERSION 3.19)
project(DroneTelemetrySimulator LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(DroneTelemetrySimulator
WIN32 MACOSX_BUNDLE
main.cpp
mainwindow.cpp
mainwindow.h
mainwindow.ui
droneworker.h droneworker.cpp
simulatorfactory.h simulatorfactory.cpp
dronesimulator.h dronesimulator.cpp
randomwalkstrategy.h randomwalkstrategy.cpp
hoverstrategy.h hoverstrategy.cpp
MovementStrategy.h
logger.h logger.cpp
telemetrymodel.h telemetrymodel.cpp
telemetrytypes.cpp
README.md
utils.h utils.cpp
)

target_link_libraries(DroneTelemetrySimulator
PRIVATE
Qt::Core
Qt::Widgets
)
target_link_libraries(DroneTelemetrySimulator PRIVATE Qt6::Core)

include(GNUInstallDirs)

install(TARGETS DroneTelemetrySimulator
BUNDLE DESTINATION .
RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
TARGET DroneTelemetrySimulator
OUTPUT_SCRIPT deploy_script
NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})


