cmake_minimum_required (VERSION 3.10)
project (Flocking)

find_package (Qt5 COMPONENTS Widgets)

set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")

set (BUILD_SHARED_LIBS OFF)

add_subdirectory(src)
