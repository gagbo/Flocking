project (Flocking-main)

set (Flocking_VERSION_MAJOR 0)
set (Flocking_VERSION_MINOR 4)


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
include_directories ("ant")
add_subdirectory (geometry)
include_directories ("geometry")
add_subdirectory (ui)
include_directories ("ui")
add_subdirectory (engine)
include_directories ("engine")


add_executable (flocks main.cpp)
target_link_libraries (flocks Qt5::Widgets)
target_link_libraries (flocks ant engine ui)

install (TARGETS flocks DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/FlockingConfig.h"
             DESTINATION include)
