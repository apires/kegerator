#include "glog/logging.h"
#include "Kegerator.hpp"
#include "gpio/GPIOLinux.hpp"
#include "ui/screens/SoundboardScreen.hpp"
#include <QApplication>
#include <QFileDialog>

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  QApplication a(argc, argv);

  auto kegerator = std::make_unique<Kegerator>();

  kegerator->AddTrackPath("/Users/apires/mp3_samples");
  kegerator->ShowSoundboard();

//  kegerator->show();
//
//  auto songs = std::getenv("KEGERATOR_SONG_LIST");
//  if (songs != nullptr) {
//    kegerator->LoadTracks(songs);
//  }

//  auto pins = std::vector<uint32_t>{21};
//  std::string path = "/dev/gpiochip0";
//  auto t = std::make_unique<gpio::GPIOLinux>(path, pins);
//
//  t->SetPinChangeCallback(21, [&kegerator](auto _pin) {
//    kegerator->PlayRandomTrack();
//  });

  return QApplication::exec();
}
