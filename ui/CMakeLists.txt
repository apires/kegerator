find_package(Qt6 COMPONENTS
        Widgets
        REQUIRED)

add_library(KegeratorUI
        MainWindow.cpp
        Player.cpp
        layouts/FlowLayout.cpp
        buttons/RoundButton.cpp screens/ConfigurationScreen.cpp screens/ConfigurationScreen.hpp screens/SoundboardScreen.cpp screens/SoundboardScreen.hpp screens/KegeratorScreen.cpp screens/KegeratorScreen.hpp)

target_link_libraries(KegeratorUI
        Qt::Widgets
        glog::glog)