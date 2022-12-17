find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(glog 0.6.0 REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(LibGPIOD REQUIRED libgpiod)

set(CMAKE_AUTOMOC ON)

add_library(KegeratorLinuxGPIO SHARED
        ../GPIO.cpp
        ../GPIO.hpp
        ../GPIOPin.cpp
        ../GPIOPin.hpp
        GPIOLinux.cpp
        GPIOLinux.hpp
        GPIOLinuxWatcher.cpp
        GPIOLinuxWatcher.hpp)

target_link_libraries(KegeratorLinuxGPIO PRIVATE
        Qt6::Core
        ${LibGPIOD_LIBRARIES})

add_executable(KegeratorLinuxGPIOTest
        KegeratorGPIOTest.cpp)

target_link_libraries(KegeratorLinuxGPIOTest PRIVATE
        KegeratorLinuxGPIO
        Qt6::Core
        glog::glog)