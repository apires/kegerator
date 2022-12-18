find_package(Qt6 REQUIRED COMPONENTS
        Core)

add_library(KegeratorGPIO
        GPIO.cpp
        GPIO.hpp
        GPIOPin.cpp
        GPIOPin.hpp)

target_link_libraries(KegeratorGPIO PRIVATE
        glog::glog
        Qt6::Core)

add_executable(GPIOTestThing
        GPIO.cpp)

target_link_libraries(GPIOTestThing PRIVATE
        KegeratorGPIO
        Qt6::Core
        glog::glog)

add_subdirectory(fake)
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_subdirectory(linux)
endif ()

