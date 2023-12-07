cmake_minimum_required(VERSION 3.5)

project(TextEditorApp LANGUAGES CXX)

# Set the minimum required version of Qt
find_package(Qt5 COMPONENTS Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# Add your source files
set(SOURCES
    texteditor.cpp
    main.cpp
)

# Add your header files
set(HEADERS
    texteditor.hpp
)

# Tell CMake to create the executable
add_executable(TextEditorApp ${SOURCES} ${HEADERS})

# Use the Widgets module from Qt 5
target_link_libraries(TextEditorApp PRIVATE Qt5::Widgets)
