cmake_minimum_required(VERSION 3.24)

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

project(ConceptApp LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(includes)

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Qml Quick Widgets QuickControls2 Svg)
find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Qml Quick Widgets QuickControls2 Svg)

if (Qt6_VERSION VERSION_GREATER_EQUAL 6.3)
    qt_standard_project_setup()
endif()

message("CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Backend/src/database ${CMAKE_CURRENT_BINARY_DIR}/database)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party ${CMAKE_CURRENT_BINARY_DIR}/third_party)

### Don't forget to add your new cpp and hpp functions here to link them with the App
qt_add_executable(ConceptApp
    src/main.cpp
    includes/mainhelp.h src/mainhelp.cpp
    includes/setFocusPeriod.h src/setFocusPeriod.cpp
    includes/export.h includes/precompiled.h
    includes/database/notes.h src/database/notes.cpp
    includes/database/folders.h src/database/folders.cpp
    includes/database/focus_time.h src/database/focus_time.cpp
    includes/timer.h src/timer.cpp
    includes/database/database.h
    includes/errors.h
    includes/todoList.h
    includes/todoItem.h
    src/todoList.cpp
    src/todoItem.cpp
)

## Configure QxOrm
include(${CMAKE_CURRENT_SOURCE_DIR}/third_party/QxOrm/QxOrm.cmake)

target_compile_definitions(ConceptApp PRIVATE -D_BUILDING_QX_CONCEPTAPP)

if(COMMAND target_precompile_headers)
    target_precompile_headers(ConceptApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes/precompiled.h)
endif() # (COMMAND target_precompile_headers)

qt_add_resources(ConceptApp "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)

target_link_libraries(ConceptApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Widgets
    Qt6::QuickControls2
    Qt6::Svg
    ${QX_LIBRARIES}
    QxOrm
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
