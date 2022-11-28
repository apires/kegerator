
add_library(KegeratorPlayer SHARED
        Player.cpp
        Track.cpp)

target_link_libraries(KegeratorPlayer
        Qt::Widgets
        glog::glog)