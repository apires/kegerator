//
// Created by Antonio Jose Pires on 11/18/22.
//

#include <dlfcn.h>
#include <filesystem>
#include "GPIO.hpp"
#include "glog/logging.h"

namespace gpio {

std::unique_ptr<gpio::GPIO> GPIO::NewFakeGPIO(const std::filesystem::path &path = "/tmp/socket.keg") {
  auto gpio_driver = dlopen("@executable_path/libKegeratorFakeGPIO.dylib", RTLD_NOW | RTLD_LOCAL);
  DLOG(INFO) << "Tried to open libKegeratorFakeGPIO.dylib, did it work? " << (gpio_driver != nullptr ? "Yes" : "No");
  if (gpio_driver == nullptr) {
    auto err = dlerror();
    DLOG(ERROR) << "\t" << err;
    return nullptr;
  }
  auto create = dlsym(gpio_driver, "create");

  DLOG(INFO) << "Do we have a create symbol? " << create;

  auto create_t =
      reinterpret_cast<gpio::GPIO *(*)(const std::filesystem::path &)>(create);

  return std::unique_ptr<GPIO>{create_t(path)};
}
} // gpio

int main() {
  auto fake = gpio::GPIO::NewFakeGPIO();
  DLOG(INFO) << fake->pins()[0];
}
