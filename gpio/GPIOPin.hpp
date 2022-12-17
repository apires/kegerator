//
// Created by Antonio Jose Pires on 12/15/22.
//

#ifndef KEGERATOR_QT_GPIO_GPIOPIN_HPP_
#define KEGERATOR_QT_GPIO_GPIOPIN_HPP_
#include <cstdint>
#include <string>
namespace gpio {

class GPIOPin {
 public:
  GPIOPin(uint32_t pin_number, bool has_pullup, std::string pin_name);
 public:
  [[nodiscard]] uint32_t Number() const;
  [[nodiscard]] bool HasPullup() const;
  [[nodiscard]] const std::string &Name() const;
  friend std::ostream &operator<<(std::ostream &outs, const gpio::GPIOPin &p);

 private:
  // Should we have some notion of direction?
  uint32_t m_pin_number;
  std::string m_pin_name;
  bool m_has_pullup; // Is there a pullup resistor to make our world upside down?
};

}
#endif //KEGERATOR_QT_GPIO_GPIOPIN_HPP_
