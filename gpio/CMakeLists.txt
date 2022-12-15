find_package(Qt6 REQUIRED COMPONENTS
        Core)

add_library(KegeratorFakeGPIO SHARED
        GPIOPin.hpp
        GPIOPin.cpp
        fake/FakeGPIO.hpp
        fake/FakeGPIO.cpp)

target_link_libraries(KegeratorFakeGPIO
        Qt::Core
        glog::glog)

add_executable(GPIOTestThing
        GPIO.hpp
        GPIO.cpp)

target_link_libraries(GPIOTestThing
        KegeratorFakeGPIO
        glog::glog)


if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(PkgConfig REQUIRED)
    pkg_search_module(LibGPIOD REQUIRED libgpiod)

    add_library(KegeratorGPIOLinux,
            GPIO.cpp
            linux/GPIOLinux.cpp
            linux/GPIOLinux.hpp
            linux/GPIOLinuxWatcher.cpp
            linux/GPIOLinuxWatcher.hpp
            ${LibGPIOD_LIBRARIES})

    add_executable(KegeratorGPIOLinuxTest
            linux/KegeratorGPIOTest.cpp)

    target_include_directories(KegeratorGPIOLinuxTest PRIVATE ${LibGPIOD_INCLUDES})
    target_link_libraries(KegeratorGPIOLinuxTest PRIVATE
            glog::glog
            Qt6::Core
            KegeratorGPIOLinux)
endif ()

