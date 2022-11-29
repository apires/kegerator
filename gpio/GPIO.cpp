//
// Created by Antonio Jose Pires on 11/18/22.
//

#include "GPIO.hpp"

namespace gpio {
void gpio::GPIO::SetPinChangeCallback(uint32_t pin, std::function<void(uint32_t)> callback) {
  m_signal_callback_map.insert({pin, std::move(callback)});
}
} // gpio
