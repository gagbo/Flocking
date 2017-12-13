include_directories (${Qt5Widgets_INCLUDE_DIRS})
include_directories (../geometry)

add_library (ant ant.cpp)
target_link_libraries (ant ${Qt5Widgets_LIBRAIRIES})
target_link_libraries (ant geometry)
qt5_use_modules (ant Widgets)

install (TARGETS ant DESTINATION bin)
install (FILES ant.h DESTINATION include)
