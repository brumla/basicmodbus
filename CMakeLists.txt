cmake_minimum_required(VERSION 3.19)
project(modbus01 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS SerialPort)

qt_standard_project_setup()

qt_add_executable(modbus01
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    common_utils.cpp common_utils.h licence.qrc modbus_utils.cpp modbus_utils.h modbusdataformatter.cpp modbusdataformatter.h
)

qt_add_translations(modbus01 TS_FILES modbus01_cz.ts)

target_link_libraries(modbus01
    PRIVATE
        Qt::Core
        Qt::Widgets
)

target_link_libraries(modbus01 PRIVATE Qt6::SerialPort)


install(TARGETS modbus01
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET modbus01
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
