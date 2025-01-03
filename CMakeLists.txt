cmake_minimum_required(VERSION 3.5)

project(crazyflie_ros2)

set(CMAKE_CXX_STANDARD 20)

# Ensure Qt MOC is enabled
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt5 packages
find_package(Qt5 REQUIRED COMPONENTS Widgets Network)

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add the executable
add_executable(CrazyFlieGUI
    src/gui_test.cpp
    src/gui.cpp
    include/gui.hpp
)

# Link against Qt5 libraries
target_link_libraries(CrazyFlieGUI Qt5::Widgets Qt5::Network)

# Ensure MOC files are generated correctly
target_include_directories(CrazyFlieGUI PRIVATE ${CMAKE_CURRENT_BINARY_DIR})