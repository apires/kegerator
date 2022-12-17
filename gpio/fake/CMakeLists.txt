find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(KegeratorFakeGPIO SHARED
        ../GPIOPin.hpp
        ../GPIOPin.cpp
        FakeGPIO.hpp
        FakeGPIO.cpp)

target_link_libraries(KegeratorFakeGPIO PRIVATE
        Qt::Core
        glog::glog)
