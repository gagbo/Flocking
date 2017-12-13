include_directories (.)
include_directories (../geometry)
include_directories (../engine)

add_library (ant ant.cpp)
target_link_libraries (ant geometry engine)

install (TARGETS ant DESTINATION bin)
install (FILES ant.h DESTINATION include)
