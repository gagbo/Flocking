include_directories (../ant)
include_directories (../geometry)
add_library (engine engineantscene.cpp)
target_link_libraries (engine ant geometry)

install (TARGETS engine DESTINATION bin)
install (FILES engineantscene.h DESTINATION include)
