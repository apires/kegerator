find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(KegeratorFakeGPIO SHARED
        FakeGPIO.hpp
        FakeGPIO.cpp)

target_link_libraries(KegeratorFakeGPIO PRIVATE
        KegeratorGPIO
        Qt::Core
        glog::glog)
