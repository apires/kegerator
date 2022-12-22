#include "glog/logging.h"
#include <QApplication>
#include <QFileDialog>
#include "Kegerator.hpp"

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  QApplication a(argc, argv);
  Kegerator k;


//  kegerator->show();

//  auto pins = std::vector<uint32_t>{21};
//  std::string path = "/dev/gpiochip0";
//  auto t = std::make_unique<gpio::GPIOLinux>(path, pins);
//
//  t->SetPinChangeCallback(21, [&kegerator](auto _pin) {
//    kegerator->PlayRandomTrack();
//  });

  return QApplication::exec();
}
