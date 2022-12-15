//
// Created by Antonio Jose Pires on 11/18/22.
//

#ifndef KEGERATOR_QT_GPIO_FAKEGPIO_HPP_
#define KEGERATOR_QT_GPIO_FAKEGPIO_HPP_

#include <QFileSystemWatcher>
#include <QFile>
#include "../GPIO.hpp"

namespace gpio {

class FakeGPIO : public GPIO {
 public:
  explicit FakeGPIO(const std::filesystem::path &watch_path);
  ~FakeGPIO() override;

  [[nodiscard]] virtual std::vector<GPIOPin> pins() const override;
  [[nodiscard]] virtual GPIOPin pin(uint32_t index) const override;
  virtual void onPinChange(const GPIOPin &pin, std::function<void(bool)>) override;

 private:
  QFileSystemWatcher m_watcher;
  QFile m_file;
  QMetaObject::Connection m_file_changed_connection;
  void OnFileChange();
  GPIOPin m_pin;
};

extern "C" FakeGPIO *create(const std::filesystem::path &path = "/tmp/socket.keg");
extern "C" [[maybe_unused]] void destroy(FakeGPIO *it);

} // gpio

#endif //KEGERATOR_QT_GPIO_FAKEGPIO_HPP_
