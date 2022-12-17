//
// Created by Antonio Jose Pires on 11/18/22.
//

#ifndef KEGERATOR_QT_GPIO_FAKEGPIO_HPP_
#define KEGERATOR_QT_GPIO_FAKEGPIO_HPP_

#include <QFileSystemWatcher>
#include <QFile>
#include <QMap>
#include "../GPIO.hpp"

namespace gpio {

class FakeGPIO : public GPIO {
 public:
  explicit FakeGPIO(const std::filesystem::path &watch_path);
  ~FakeGPIO() override;

  [[nodiscard]]  std::vector<GPIOPin> pins() const override;
  [[nodiscard]] GPIOPin pin(uint16_t index) const override;

 private:
  QFileSystemWatcher m_watcher;
  QMetaObject::Connection m_file_changed_connection;

  QFile m_file;
  void OnFileChange();
};

extern "C" GPIO *kegerator_create_gpio_device(const std::filesystem::path &path);
extern "C" void *kegerator_list_gpio_devices();
}
// gpio

#endif //KEGERATOR_QT_GPIO_FAKEGPIO_HPP_
