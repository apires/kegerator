#include "glog/logging.h"
#include "Kegerator.hpp"
#include "gpio/FakeGPIO.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  QApplication a(argc, argv);

  auto kegerator = std::make_unique<Kegerator>();
  kegerator->show();

  auto songs = std::getenv("KEGERATOR_SONG_LIST");
  if (songs != nullptr) {
    kegerator->LoadTracks(songs);
  }

  auto t = gpio::FakeGPIO();

  t.SetPinChangeCallback(2, [&kegerator](auto _pin) {
    kegerator->PlayRandomTrack();
  });

  return QApplication::exec();
}
