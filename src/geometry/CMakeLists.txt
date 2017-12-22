# Geometry library
add_library (geometry victor.cpp)

# Test case for the geometry library
add_executable(test_geometry test_geometry.cpp)
target_link_libraries(test_geometry geometry)
target_link_libraries(test_geometry Qt5::Widgets Qt5::Test)

add_test(test_geometry test_geometry)

# Install location
install (TARGETS geometry DESTINATION bin)
install (TARGETS test_geometry DESTINATION bin)
install (FILES victor.h DESTINATION include)
