//
// Created by Antonio Jose Pires on 11/18/22.
//

#ifndef KEGERATOR_QT_GPIO_FAKEGPIO_HPP_
#define KEGERATOR_QT_GPIO_FAKEGPIO_HPP_

#include <QFileSystemWatcher>
#include <QFile>
#include "GPIO.hpp"

namespace gpio {

class FakeGPIO : public gpio::GPIO {
 public:
  explicit FakeGPIO();
  ~FakeGPIO() override;
  void SetPinChangeCallback(uint pin, std::function<void(uint)> callback) override;

 private:
  QFileSystemWatcher m_watcher;
  QFile m_file;
  QMetaObject::Connection m_file_changed_connection;
  std::map<uint, std::function<void(uint pin)> &> m_signal_callback_map;

  void OnFileChange(const QString &path);
};

} // gpio

#endif //KEGERATOR_QT_GPIO_FAKEGPIO_HPP_
