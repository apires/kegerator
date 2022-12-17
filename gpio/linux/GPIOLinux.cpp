//
// Created by Antonio Jose Pires on 11/28/22.
//

#include <string>
#include <filesystem>
#include "glog/logging.h"
#include "GPIOLinux.hpp"
#include "gpiod.h"

namespace gpio {

std::vector<std::filesystem::path> GPIOLinux::ListGPIODevices() {
  auto device_list = std::vector<std::filesystem::path>();
  auto iter = gpiod_chip_iter_new();

  gpiod_chip *chip;
  DLOG(INFO) << "Probing GPIO devices...";
  while ((chip = gpiod_chip_iter_next(iter)) != NULL) {
    auto name = gpiod_chip_name(chip);
    device_list.emplace_back(name);
    DLOG(INFO) << "\tChip : " << name;
  }
  DLOG(INFO) << "Done probing GPIO devices.";

  // Will this deallocate our names? Supposed to just free the iterator I guess.
  gpiod_chip_iter_free(iter);
  return device_list;
}

std::vector<GPIOPin> GPIOLinux::pins() const {

  auto line_list = std::vector<GPIOPin>();
  auto chip = gpiod_chip_open(m_gpio_device.c_str());
  auto lines_iterator = gpiod_line_iter_new(chip);

  for (auto line = gpiod_line_iter_next(lines_iterator); line != nullptr;
       line = gpiod_line_iter_next(lines_iterator)) {

    line_list.emplace_back(gpiod_line_offset(line),
                           gpiod_line_active_state(line) == GPIOD_LINE_ACTIVE_STATE_LOW,
                           gpiod_line_name(line));
  }

  gpiod_line_iter_free(lines_iterator);
  return line_list;
}
GPIOPin GPIOLinux::pin(uint16_t pin_number) const {
  auto pin = gpiod_line_get(m_gpio_device.c_str(), pin_number);
  return {pin_number, gpiod_line_active_state(pin) == GPIOD_LINE_ACTIVE_STATE_LOW,
          gpiod_line_name(pin)};

}
GPIOLinux::GPIOLinux(const std::filesystem::path &device)
    : m_gpio_device(device), m_watcher(new GPIOLinuxWatcher(device)) {

  QObject::connect(m_watcher, &GPIOLinuxWatcher::pinDepressed, [this](uint32_t pin_number) {
    if (!m_pin_to_callback.contains(pin_number)) {
      DLOG(INFO) << "We do not have a callback registered for pin " << pin_number;
      return;
    }
    auto pin_callback = m_pin_to_callback[pin_number];
    pin_callback(true);
  });
}

GPIOLinux::~GPIOLinux() {
  m_watcher->disconnect();
  delete m_watcher;
}

GPIO *kegerator_create_gpio_device(const std::filesystem::path &path) {
  DLOG(INFO) << "Creating GPIOLinux";
  return new GPIOLinux(path);
}
void *kegerator_list_gpio_devices() {
  return new std::vector(GPIOLinux::ListGPIODevices());
}

} // gpio
