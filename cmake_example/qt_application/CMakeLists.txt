cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(cmake_qt_demo
	DESCRIPTION "hello_world_qt"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

add_executable(${PROJECT_NAME}
    src/main.cpp
	src/window.cpp
	
	src/window.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
	Qt${QT_VERSION_MAJOR}::Core 
	Qt${QT_VERSION_MAJOR}::Widgets
)
