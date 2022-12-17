//
// Created by Antonio Jose Pires on 11/28/22.
//

#ifndef KEGERATOR_QT_GPIO_GPIOLINUX_HPP_
#define KEGERATOR_QT_GPIO_GPIOLINUX_HPP_

#include "../GPIO.hpp"
#include "GPIOLinuxWatcher.hpp"
#include <filesystem>

namespace gpio {

class GPIOLinux : public gpio::GPIO {
 public:
  explicit GPIOLinux(const std::filesystem::path &device);
  ~GPIOLinux() override;

  [[nodiscard]]  std::vector<GPIOPin> pins() const override;
  [[nodiscard]]  GPIOPin pin(uint16_t pin) const override;

  static std::vector<std::filesystem::path> ListGPIODevices();

 private:
  const std::filesystem::path &m_gpio_device;
  GPIOLinuxWatcher *m_watcher;
};

extern "C" GPIO *kegerator_create_gpio_device(const std::filesystem::path &path);
extern "C" void *kegerator_list_gpio_devices();

} // gpio

#endif //KEGERATOR_QT_GPIO_GPIOLINUX_HPP_
