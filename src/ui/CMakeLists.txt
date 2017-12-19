include_directories (../engine)

add_library (ui ui.cpp mainwindow.cpp engineview.cpp)
target_link_libraries (ui Qt5::Widgets)
target_link_libraries (ui engine)

install (TARGETS ui DESTINATION bin)
install (FILES ui.h mainwindow.h engineview.h DESTINATION include)
