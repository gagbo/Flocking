cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 14)
project (Flocking)

find_package (Qt5 5.9 COMPONENTS Widgets Test REQUIRED QUIET)

set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")

set (BUILD_SHARED_LIBS OFF)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -fprofile-arcs -ftest-coverage")

enable_testing()

add_subdirectory(src)
