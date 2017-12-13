include_directories (.)
add_library (geometry victor.cpp)

install (TARGETS geometry DESTINATION bin)
install (FILES victor.h DESTINATION include)
