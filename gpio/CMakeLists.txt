find_package(Qt6 REQUIRED COMPONENTS
        Core)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(KegeratorGPIO
        FakeGPIO.cpp
        GPIO.cpp)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(PkgConfig REQUIRED)
    pkg_search_module(LibGPIOD REQUIRED libgpiod)

    add_executable(KegeratorGPIOLinuxTest
            GPIOLinux.cpp
            GPIOLinux.hpp
            GPIOLinuxWatcher.cpp
            GPIOLinuxWatcher.hpp
            KegeratorGPIOTest.cpp
            )

    target_include_directories(KegeratorGPIOLinuxTest PRIVATE ${LibGPIOD_INCLUDES})
    target_link_libraries(KegeratorGPIOLinuxTest PRIVATE
            ${LibGPIOD_LIBRARIES}
            glog::glog
            Qt6::Core
            KegeratorGPIO)
else ()
    message(FATAL_ERROR, "We don't know how to build GPIO for ${CMAKE_SYSTEM_NAME}")
endif ()


target_link_libraries(KegeratorGPIO
        Qt::Core
        glog::glog)
