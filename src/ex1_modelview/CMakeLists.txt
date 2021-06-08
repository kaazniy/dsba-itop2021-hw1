
add_executable(ModelView
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    examplemodel.cpp
    examplemodel.h
    renderarea.h
    renderarea.cpp
    aboutdialog.cpp
    aboutdialog.h
    aboutdialog.ui
)
target_link_libraries(ModelView Qt5::Widgets)
