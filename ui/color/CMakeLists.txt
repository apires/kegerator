find_package(Qt6 COMPONENTS
        Core
        Gui
        REQUIRED)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(ENV{OPENSSL_ROOT_DIR} "/opt/homebrew/opt/openssl@1.1")
endif ()

find_package(OpenSSL 1.1.1 REQUIRED)
qt_add_library(color ColorPicker.cpp)

target_include_directories(color PRIVATE
        ${OPENSSL_INCLUDE_DIR})

target_link_libraries(color
        Qt6::Core
        Qt6::Gui
        ${OPENSSL_LIBRARIES})
