cmake_minimum_required(VERSION 3.5)

project(rov_gui)

set(CMAKE_CXX_STANDARD 20)

# Ensure Qt MOC is enabled
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt5 packages
find_package(Qt5 REQUIRED COMPONENTS Widgets Network)

# Find QCustomPlot
find_path(QCUSTOMPLOT_INCLUDE_DIR qcustomplot.h)
find_library(QCUSTOMPLOT_LIBRARY qcustomplot)

if (NOT QCUSTOMPLOT_INCLUDE_DIR OR NOT QCUSTOMPLOT_LIBRARY)
    message(FATAL_ERROR "QCustomPlot not found. Please install it via apt or provide the source files.")
endif()

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${QCUSTOMPLOT_INCLUDE_DIR})

# Add the executable
add_executable(rov_gui
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
    src/gui/pid_gui.cpp
    src/gui/altitude_gui.cpp
    include/gui/gui.hpp
    include/gui/udp_sniffer_gui.hpp
    include/gui/configuration_gui.hpp
    include/gui/buttons_gui.hpp
    include/gui/compass_gui.hpp
    include/gui/thrusters_gui.hpp
    include/gui/indicator_gui.hpp
    include/gui/waypoint_list.hpp
    include/gui/number_display.hpp
    include/gui/depth_altitude_plot.hpp
    include/gui/pid_gui.hpp
    include/gui/altitude_gui.hpp
    resources.qrc
)

# Link against Qt5 libraries
target_link_libraries(rov_gui Qt5::Widgets Qt5::Network ${QCUSTOMPLOT_LIBRARY})

# Ensure MOC files are generated correctly
target_include_directories(rov_gui PRIVATE ${CMAKE_CURRENT_BINARY_DIR})