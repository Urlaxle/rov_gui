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
    src/gui/gui_test.cpp
    src/gui/gui.cpp
    src/gui/configuration_gui.cpp
    src/gui/udp_sniffer_gui.cpp
    src/gui/buttons_gui.cpp
    src/gui/compass_gui.cpp
    src/gui/thrusters_gui.cpp
    src/gui/indicator_gui.cpp
    src/gui/waypoint_list.cpp
    src/gui/number_display.cpp
    include/gui/gui.hpp
    include/gui/udp_sniffer_gui.hpp
    include/gui/configuration_gui.hpp
    include/gui/buttons_gui.hpp
    include/gui/compass_gui.hpp
    include/gui/thrusters_gui.hpp
    include/gui/indicator_gui.hpp
    include/gui/waypoint_list.hpp
    include/gui/number_display.hpp
    resources.qrc
)

# Link against Qt5 libraries
target_link_libraries(CrazyFlieGUI Qt5::Widgets Qt5::Network)

# Ensure MOC files are generated correctly
target_include_directories(CrazyFlieGUI PRIVATE ${CMAKE_CURRENT_BINARY_DIR})