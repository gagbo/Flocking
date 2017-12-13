include_directories (.)

add_library (ui ui.cpp)

install (TARGETS ui DESTINATION bin)
install (FILES ui.h DESTINATION include)
