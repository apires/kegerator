cmake_minimum_required(VERSION 3.13)
project(kegerator_qt)

set(WITH_GFLAGS OFF)
set(WITH_UNWIND OFF)
set(WITH_GTEST OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED)

add_executable(kegerator_qt main.cpp lib/FlowLayout.cpp lib/FlowLayout.hpp ui/RoundButton.cpp ui/RoundButton.hpp ui/MainWindow.cpp ui/MainWindow.hpp player/Track.cpp player/Track.hpp ui/Player.cpp ui/Player.hpp player/Player.cpp player/Player.hpp Kegerator.cpp Kegerator.hpp)


if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_subdirectory(vendor/glog)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(WITH_UNWIND ON)
    find_package(glog 0.6.0 REQUIRED)
else ()
    message(FATAL_ERROR, "We don't know how to build for ${CMAKE_SYSTEM_NAME}")
endif ()


target_link_libraries(kegerator_qt
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt6::Multimedia
        glog::glog
        )