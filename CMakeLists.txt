cmake_minimum_required (VERSION 3.10)
project (Flocking)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")

set (BUILD_SHARED_LIBS OFF)

add_subdirectory(src)
