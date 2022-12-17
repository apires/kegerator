//
// Created by Antonio Jose Pires on 11/18/22.
//

#ifndef KEGERATOR_QT_GPIO_GPIO_HPP_
#define KEGERATOR_QT_GPIO_GPIO_HPP_

#include <filesystem>
#include <functional>
#include "glog/logging.h"
#include "GPIOPin.hpp"
#include <QMap>

namespace gpio {

class GPIO {
 public:
  using PinChangeCallback_t = const std::function<void(bool)> &;

  virtual ~GPIO() = default;
  [[nodiscard]] virtual std::vector<GPIOPin> pins() const = 0;
  [[nodiscard]] virtual GPIOPin pin(uint16_t pin) const = 0;
  void registerPinChangeCallback(uint16_t pin, PinChangeCallback_t);

  static std::unique_ptr<GPIO> NewFakeGPIO(const std::filesystem::path &path);
  static std::unique_ptr<GPIO> NewLinuxGPIO(const std::filesystem::path &device);
  static std::vector<std::filesystem::path> ListFakeGPIODevices();
  static std::vector<std::filesystem::path> ListLinuxGPIODevices();

 protected:
  using GPIOFactory_t = GPIO *(*)(const std::filesystem::path &);
  using GPIOListDevices_t = std::vector<std::filesystem::path> *(*)();
  QMap<uint32_t, std::function<void(bool)>> m_pin_to_callback;

  static std::unique_ptr<GPIO> tryConstructFromDriver(void *gpio_driver, const std::filesystem::path &arg);
  static std::vector<std::filesystem::path> tryListDevicesFromDriver(void *gpio_driver);
};

} // gpio


#endif //KEGERATOR_QT_GPIO_GPIO_HPP_
