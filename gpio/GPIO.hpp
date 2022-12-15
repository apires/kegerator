//
// Created by Antonio Jose Pires on 11/18/22.
//

#ifndef KEGERATOR_QT_GPIO_GPIO_HPP_
#define KEGERATOR_QT_GPIO_GPIO_HPP_

#include <cstdint>
#include <functional>
#include <map>
#include "glog/logging.h"
#include "GPIOPin.hpp"

namespace gpio {

class GPIO {
 public:
//  void SetPinChangeCallback(uint32_t pin, std::function<void(uint32_t)> callback);
  virtual ~GPIO() = default;
  [[nodiscard]] virtual std::vector<GPIOPin> pins() const = 0;
  [[nodiscard]] virtual GPIOPin pin(uint32_t index) const = 0;
  virtual void onPinChange(const GPIOPin &pin, std::function<void(bool)>) = 0;

  static std::unique_ptr<gpio::GPIO> NewFakeGPIO(const std::filesystem::path &path);

// protected:
//  std::map<uint32_t, std::function<void(uint32_t)>> m_signal_callback_map;
};

} // gpio


#endif //KEGERATOR_QT_GPIO_GPIO_HPP_
