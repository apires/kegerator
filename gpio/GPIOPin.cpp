//
// Created by Antonio Jose Pires on 12/15/22.
//

#include "GPIOPin.hpp"
#include <iostream>

namespace gpio {

GPIOPin::GPIOPin(uint32_t pin_number, bool has_pullup, std::string pin_name)
    : m_pin_number(pin_number), m_pin_name(std::move(pin_name)), m_has_pullup(has_pullup) {}

uint32_t GPIOPin::PinNumber() const {
  return m_pin_number;
}
const std::string &GPIOPin::PinName() const {
  return m_pin_name;
}
bool GPIOPin::HasPullup() const {
  return m_has_pullup;
}

std::ostream &operator<<(std::ostream &outs, const gpio::GPIOPin &p) {
  auto pinName = p.m_pin_name.empty() ? "No Name" : p.m_pin_name;
  auto hasPullup = p.HasPullup() ? "Yes" : "No";
  return outs << "(GPIOPin number=[" << p.m_pin_number << "] name=\"" << pinName << "\" hasPullup?=[" << hasPullup
              << "])";
}

}
