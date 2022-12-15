//
// Created by Antonio Jose Pires on 11/27/22.
//

#include "glog/logging.h"
#include "gpiod.h"
#include <QCoreApplication>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  google::InitGoogleLogging(argv[0]);
  google::SetStderrLogging(google::GLOG_INFO);
  LOG(INFO) << "GPIO Test";

  auto iter = gpiod_chip_iter_new();

  for (auto chip = gpiod_chip_iter_next(iter); chip != nullptr; chip = gpiod_chip_iter_next(iter)) {

    LOG(INFO) << gpiod_chip_name(chip) << " - " << gpiod_chip_num_lines(chip) << " lines:" << ::std::endl;

    auto lines_iterator = gpiod_line_iter_new(chip);

    for (auto line = gpiod_line_iter_next(lines_iterator); line != nullptr;
         line = gpiod_line_iter_next(lines_iterator)) {

      LOG(INFO) << "line " << gpiod_line_offset(line) << ": ";

      if (auto x = gpiod_line_name(line)) {
        LOG(INFO) << "\tName: " << ((strlen(x) == 0) ? "unnamed" : x);
      }

      if (auto x = gpiod_line_consumer(line)) {
        LOG(INFO) << "\tConsumer: " << ((strlen(x) == 0) ? "unused" : x);
      }

      LOG(INFO) << "\tDirection: " << (gpiod_line_direction(line) == GPIOD_LINE_DIRECTION_INPUT ? "input" : "output");

      LOG(INFO) << "\tActive State: " << (gpiod_line_active_state(line) == GPIOD_LINE_ACTIVE_STATE_LOW
                                          ? "active-low" : "active-high");

      LOG(INFO) << ::std::endl;
    }

  }
  QCoreApplication::exec();
}
