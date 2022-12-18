cmake_minimum_required(VERSION 3.13)
project(kegerator_qt)

set(WITH_GFLAGS OFF)
set(WITH_UNWIND OFF)
set(WITH_GTEST OFF)

set(CMAKE_CXX_STANDARD 20)

find_package(glog 0.6.0 REQUIRED)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(WITH_UNWIND ON)
endif ()

add_subdirectory(ui)
add_subdirectory(player)
add_subdirectory(gpio)

add_executable(kegerator_qt main.cpp Kegerator.cpp)

target_link_libraries(kegerator_qt
        glog::glog
        KegeratorUI
        KegeratorPlayer
        KegeratorGPIO)