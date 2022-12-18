//
// Created by Antonio Jose Pires on 11/27/22.
//

#include "glog/logging.h"
#include "GPIOLinux.hpp"
#include <QCoreApplication>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  google::InitGoogleLogging(argv[0]);
  google::SetStderrLogging(google::GLOG_INFO);
  LOG(INFO) << "GPIO Test";
  auto gpio_devices = gpio::GPIOLinux::ListGPIODevices();
  if (gpio_devices.empty()) {
    LOG(INFO) << "No devices found, sorry";
    return -1;
  }

  for (auto &device : gpio_devices) {
    LOG(INFO) << '\t' << device;
  }
}
