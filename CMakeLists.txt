cmake_minimum_required(VERSION 3.16)

project(clinicTest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick Sql REQUIRED)

qt_add_executable(appclinicTest
    main.cpp
#    databasehandler.h
#    databasehandler.cpp
    databasehelper.h
    databasehelper.cpp
)

qt_add_qml_module(appclinicTest
    URI clinicTest
    VERSION 1.0
    QML_FILES main.qml 
)

set_target_properties(appclinicTest PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appclinicTest
    PRIVATE Qt6::Quick Qt6::Sql)

install(TARGETS appclinicTest
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
