//
// Created by Antonio Jose Pires on 11/18/22.
//

#include <dlfcn.h>
#include <filesystem>
#include "GPIO.hpp"
#include "glog/logging.h"

namespace gpio {

std::unique_ptr<gpio::GPIO> GPIO::NewFakeGPIO(const std::filesystem::path &path = "/tmp/socket.keg") {
#ifdef __linux__
  auto gpio_driver = dlopen("fake/libKegeratorFakeGPIO.so", RTLD_NOW | RTLD_LOCAL);
  DLOG(INFO) << "Tried to open libKegeratorFakeGPIO.so, did it work? " << (gpio_driver != nullptr ? "Yes" : "No");
#endif
#ifdef __APPLE__
  auto gpio_driver = dlopen("@executable_path/libKegeratorFakeGPIO.dylib", RTLD_NOW | RTLD_LOCAL);
  DLOG(INFO) << "Tried to open libKegeratorFakeGPIO.dylib, did it work? " << (gpio_driver != nullptr ? "Yes" : "No");
#endif
  return tryConstructFromDriver(gpio_driver, path);
}

std::vector<std::filesystem::path> GPIO::ListFakeGPIODevices() {
#ifdef __linux__
  auto gpio_driver = dlopen("fake/libKegeratorFakeGPIO.so", RTLD_NOW | RTLD_LOCAL);
  DLOG(INFO) << "Tried to open libKegeratorFakeGPIO.so, did it work? " << (gpio_driver != nullptr ? "Yes" : "No");
#endif
#ifdef __APPLE__
  auto gpio_driver = dlopen("@executable_path/libKegeratorFakeGPIO.dylib", RTLD_NOW | RTLD_LOCAL);
  DLOG(INFO) << "Tried to open libKegeratorFakeGPIO.dylib, did it work? " << (gpio_driver != nullptr ? "Yes" : "No");
#endif
  return tryListDevicesFromDriver(gpio_driver);
}

std::unique_ptr<gpio::GPIO> GPIO::NewLinuxGPIO(const std::filesystem::path &device) {
  auto gpio_driver = dlopen("linux/KegeratorLinuxGPIO.so", RTLD_NOW | RTLD_LOCAL);
  DLOG(INFO) << "Tried to open KegeratorLinuxGPIO.so, did it work? " << (gpio_driver != nullptr ? "Yes" : "No");
  return tryConstructFromDriver(gpio_driver, device);
}

std::vector<std::filesystem::path> GPIO::ListLinuxGPIODevices() {
  auto gpio_driver = dlopen("linux/KegeratorLinuxGPIO.so", RTLD_NOW | RTLD_LOCAL);
  DLOG(INFO) << "Tried to open KegeratorLinuxGPIO.so, did it work? " << (gpio_driver != nullptr ? "Yes" : "No");
  return tryListDevicesFromDriver(gpio_driver);
}

void GPIO::registerPinChangeCallback(uint16_t pin, PinChangeCallback_t cb) {
  if (m_pin_to_callback.contains(pin)) {
    LOG(INFO) << "Warning: We already have a callback registered for pin [" << pin << "], overwriting it.";
  }
  m_pin_to_callback[pin] = cb;
}

std::unique_ptr<GPIO> GPIO::tryConstructFromDriver(void *gpio_driver, const std::filesystem::path &arg) {
  if (gpio_driver == nullptr) {
    auto err = dlerror();
    DLOG(ERROR) << "\t" << err;
    return nullptr;
  }
  auto create = dlsym(gpio_driver, "kegerator_create_gpio_device");
  DLOG(INFO) << "Do we have a create symbol? " << create;

  auto create_t = reinterpret_cast<GPIOFactory_t>(create);
  return std::unique_ptr<GPIO>{create_t(arg)};
}

std::vector<std::filesystem::path> GPIO::tryListDevicesFromDriver(void *gpio_driver) {
  if (gpio_driver == nullptr) {
    auto err = dlerror();
    DLOG(ERROR) << "\t" << err;
    return {};
  }
  auto list = dlsym(gpio_driver, "kegerator_list_gpio_devices");
  DLOG(INFO) << "Do we have a create symbol? " << list;

  auto list_t = reinterpret_cast<GPIOListDevices_t>(list);
  return *list_t();
}

} // gpio

int main() {
  auto fake = gpio::GPIO::NewFakeGPIO();
  auto devices = gpio::GPIO::ListFakeGPIODevices();
  DLOG(INFO) << devices[0];
}
