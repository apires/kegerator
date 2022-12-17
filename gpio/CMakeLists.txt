find_package(Qt6 REQUIRED COMPONENTS
        Core)

add_executable(GPIOTestThing
        GPIO.hpp
        GPIO.cpp)

target_link_libraries(GPIOTestThing PRIVATE
        Qt6::Core
        glog::glog)

add_subdirectory(fake)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_subdirectory(linux)
endif ()

