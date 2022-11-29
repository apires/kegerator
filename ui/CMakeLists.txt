find_package(Qt6 COMPONENTS
        Widgets
        REQUIRED)

add_library(KegeratorUI
        MainWindow.cpp
        Player.cpp
        FlowLayout.cpp
        RoundButton.cpp)

target_link_libraries(KegeratorUI
        Qt::Widgets
        glog::glog)