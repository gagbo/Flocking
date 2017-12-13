include_directories (.)

add_library (engine engine.cpp)

install (TARGETS engine DESTINATION bin)
install (FILES engine.h DESTINATION include)
