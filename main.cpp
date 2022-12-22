#include "glog/logging.h"
#include <QApplication>
#include <QFileDialog>
#include "Kegerator.hpp"

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  QApplication a(argc, argv);
  Kegerator k;

  return QApplication::exec();
}
