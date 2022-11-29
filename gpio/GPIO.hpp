//
// Created by Antonio Jose Pires on 11/18/22.
//

#ifndef KEGERATOR_QT_GPIO_GPIO_HPP_
#define KEGERATOR_QT_GPIO_GPIO_HPP_

#include <QObject>

namespace gpio {

class GPIO : public QObject {
 public:
  void SetPinChangeCallback(uint32_t pin, std::function<void(uint32_t)> callback);
 protected:
  std::map<uint32_t, std::function<void(uint32_t)>> m_signal_callback_map;
};

} // gpio


#endif //KEGERATOR_QT_GPIO_GPIO_HPP_
