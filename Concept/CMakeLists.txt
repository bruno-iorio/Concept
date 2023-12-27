cmake_minimum_required(VERSION 3.24)

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

project(ConceptApp LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(QML_IMPORT_PATHS "./imports/Concept/")

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Qml Quick Widgets QuickControls2 Svg)

if (Qt6_VERSION VERSION_GREATER_EQUAL 6.3)
    qt_standard_project_setup()
endif()

message("CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Backend/src/database ${CMAKE_CURRENT_BINARY_DIR}/database)

### Don't forget to add your new cpp and hpp functions here to link them with the App
qt_add_executable(ConceptApp
    src/main.cpp
)

qt_add_resources(ConceptApp "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)

target_link_libraries(ConceptApp PRIVATE
    Qt6::Core
    Qt6::Qml
    Qt6::Quick
    Qt6::Widgets
    Qt6::QuickControls2
    Qt6::Svg
    database
)

if (BUILD_QDS_COMPONENTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/qmlcomponents)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)

if (LINK_INSIGHT)
    include(${CMAKE_CURRENT_SOURCE_DIR}/insight)
endif ()

include(GNUInstallDirs)
install(TARGETS ConceptApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
