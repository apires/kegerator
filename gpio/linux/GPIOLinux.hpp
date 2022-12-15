//
// Created by Antonio Jose Pires on 11/28/22.
//

#ifndef KEGERATOR_QT_GPIO_GPIOLINUX_HPP_
#define KEGERATOR_QT_GPIO_GPIOLINUX_HPP_

#include "../GPIO.hpp"
#include "GPIOLinuxWatcher.hpp"

namespace gpio {

class GPIOLinux : public gpio::GPIO {
 public:
  explicit GPIOLinux(std::string path);
  GPIOLinux(std::string path, std::vector<uint32_t> pins);

 private:
  GPIOLinuxWatcher *m_watcher;
};

} // gpio

#endif //KEGERATOR_QT_GPIO_GPIOLINUX_HPP_
