cmake_minimum_required(VERSION 3.16)

project(dashbar VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)
qt_standard_project_setup()

qt_add_executable(dashbar
    mainwindow.ui
    application.cpp
    applicationRules.cpp
    applications.cpp
    buttonManager.cpp
    config.cpp
    fileDialog.cpp
    flowlayout.cpp
    mainwindow.cpp
    mapper.cpp
    windowPositionManager.cpp
    main.cpp
)

target_link_libraries(dashbar PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)

set_target_properties(dashbar PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
