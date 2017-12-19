include_directories (../geometry)

add_library (ant ant.cpp)
target_link_libraries (ant Qt5::Widgets)
target_link_libraries (ant geometry)

install (TARGETS ant DESTINATION bin)
install (FILES ant.h DESTINATION include)
