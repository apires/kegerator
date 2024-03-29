find_package(Qt6 COMPONENTS
        Widgets
        Core
        Svg
        REQUIRED)

qt_add_library(KegeratorToast
        Toast.cpp
        Toast.hpp)

target_link_libraries(KegeratorToast PRIVATE
        glog::glog
        Qt::Widgets)

qt_add_library(KegeratorUI
        Player.cpp
        layouts/FlowLayout.cpp
        buttons/RoundButton.cpp
        screens/ConfigurationScreen.cpp
        screens/ConfigurationScreen.hpp
        screens/SoundboardScreen.cpp
        screens/SoundboardScreen.hpp
        screens/KegeratorScreen.cpp
        screens/KegeratorScreen.hpp
        MainWindow.cpp
        MainWindow.hpp
        Toast.cpp
        Toast.hpp)

add_subdirectory(color)


target_link_libraries(KegeratorUI
        Qt::Widgets
        glog::glog)

qt6_add_resources(KegeratorUI "KegeratorAssets"
        PREFIX "/kegerator"
        FILES
        svg/grid-menu.svg
        svg/close.svg
        svg/open-folder-audio.svg)
