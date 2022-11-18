#include "glog/logging.h"
#include "Kegerator.hpp"
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

  return QApplication::exec();
}
