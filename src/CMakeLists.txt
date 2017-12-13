project (Flocking-main)

set (Flocking_VERSION_MAJOR 0)
set (Flocking_VERSION_MINOR 1)


# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
    "${PROJECT_SOURCE_DIR}/FlockingConfig.h.in"
    "${PROJECT_BINARY_DIR}/FlockingConfig.h"
    )

# add the binary tree to the search path for include files
# so that we will find FlockingConfig.h
include_directories ("${PROJECT_BINARY_DIR}")
add_subdirectory (ant)
add_subdirectory (geometry)

add_executable (flocks main.cpp)
target_link_libraries (flocks ant)

install (TARGETS flocks DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/FlockingConfig.h"
             DESTINATION include)
