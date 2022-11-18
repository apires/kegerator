//
// Created by Antonio Jose Pires on 11/18/22.
//

#ifndef KEGERATOR_QT_GPIO_GPIO_HPP_
#define KEGERATOR_QT_GPIO_GPIO_HPP_

#include <QObject>

namespace gpio {

class GPIO : public QObject {
 public:
  virtual void SetPinChangeCallback(uint pin, std::function<void(uint)> callback) = 0;
};

} // gpio


#endif //KEGERATOR_QT_GPIO_GPIO_HPP_
