//
// Created by Antonio Jose Pires on 11/18/22.
//

#ifndef KEGERATOR_QT_GPIO_FAKEGPIO_HPP_
#define KEGERATOR_QT_GPIO_FAKEGPIO_HPP_

#include <QFileSystemWatcher>
#include <QFile>

namespace gpio {

class FakeGPIO : public QObject {
 public:
  explicit FakeGPIO();
  ~FakeGPIO() override;
  void SetPinChangeCallback(u_int pin, std::function<void(u_int)> callback);

 private:
  QFileSystemWatcher m_watcher;
  QFile m_file;
  QMetaObject::Connection m_file_changed_connection;
  std::map<u_int, std::function<void(u_int pin)> &> m_signal_callback_map;

  void OnFileChange(const QString &path);
};

} // gpio

#endif //KEGERATOR_QT_GPIO_FAKEGPIO_HPP_
