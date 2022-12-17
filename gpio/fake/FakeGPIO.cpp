//
// Created by Antonio Jose Pires on 11/18/22.
//

#include <QFile>
#include "FakeGPIO.hpp"
#include "glog/logging.h"
#include <iostream>
#include <utility>

namespace gpio {

FakeGPIO::FakeGPIO(const std::filesystem::path &watch_path)
    : GPIO(), m_file(watch_path) {
  google::InitGoogleLogging("FakeGPIO");

  auto ok = m_file.open(QIODevice::ReadWrite);
  if (!ok) {
    throw std::invalid_argument("bad file");
  }

  m_watcher.addPath(QString::fromStdString(watch_path));
  QFileSystemWatcher::connect(&m_watcher, &QFileSystemWatcher::fileChanged, [this]() {
    OnFileChange();
  });

}

void FakeGPIO::OnFileChange() {
  if (m_file.size() == 0) { return; }

  auto buffer = m_file.readAll();
  bool ok = false;
  auto pin_number = buffer.toUInt(&ok);
  if (!ok) {
    DLOG(ERROR) << "Invalid pin command - " << buffer.toStdString();
    return;
  }
  if (!m_pin_to_callback.contains(pin_number)) {
    DLOG(INFO) << "We do not have a callback registered for pin " << pin_number;
    return;
  }
  auto pin_callback = m_pin_to_callback[pin_number];
  pin_callback(true);

  // now that we've processed the file, we're going to truncate it
  // so that the only line always reflect the pin being processed
  m_file.resize(0);
}

FakeGPIO::~FakeGPIO() {
  GPIO::~GPIO();
  // Are we leaking the m_watcher members and fds?
  DLOG(INFO) << "Disposing FakeGPIO";

  m_file.remove();
}
std::vector<GPIOPin> FakeGPIO::pins() const {
  auto out = std::vector<GPIOPin>();
  out.reserve(static_cast<unsigned long>(m_pin_to_callback.size()));

  for (auto i = 0; i < m_pin_to_callback.size(); i++) {
    out.emplace_back(pin(static_cast<uint16_t>(i)));
  }
  return out;
}
GPIOPin FakeGPIO::pin(uint16_t index) const {
  auto pinName = QString("FakeGPIO[%s]").arg(m_file.fileName());
  return {index, false, pinName.toStdString()};
}

GPIO *kegerator_create_gpio_device(const std::filesystem::path &path) {
  DLOG(INFO) << "Creating FakeGPIO";
  return new FakeGPIO(path);
}
void *kegerator_list_gpio_devices() {
  return new std::vector<std::filesystem::path>{"/tmp/socket.keg"};
}

} // gpio
