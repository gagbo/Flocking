include_directories (${Qt5Widgets_INCLUDE_DIRS})
include_directories (../engine)

add_library (ui ui.cpp mainwindow.cpp engineview.cpp)
target_link_libraries (ui ${Qt5Widgets_LIBRAIRIES})
target_link_libraries (ui engine)
qt5_use_modules (ui Widgets)

install (TARGETS ui DESTINATION bin)
install (FILES ui.h mainwindow.h engineview.h DESTINATION include)
