find_package(Qt6 REQUIRED COMPONENTS Multimedia)

add_library(KegeratorPlayer
        AudioPlayer.cpp
        AudioTrack.cpp)

target_link_libraries(KegeratorPlayer
        Qt6::Multimedia
        glog::glog)