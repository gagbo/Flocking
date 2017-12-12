include_directories (.)
add_library (geometry vector.cpp)

install (TARGETS geometry DESTINATION bin)
install (FILES vector.h DESTINATION include)
