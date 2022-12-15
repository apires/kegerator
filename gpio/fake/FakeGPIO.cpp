//
// Created by Antonio Jose Pires on 11/18/22.
//

#include <QFile>
#include "FakeGPIO.hpp"
#include "glog/logging.h"
#include <iostream>

namespace gpio {

FakeGPIO::FakeGPIO(const std::filesystem::path &watch_path)
    : GPIO(), m_file(watch_path), m_pin(GPIOPin(0, false, m_file.fileName().toStdString())) {
  google::InitGoogleLogging("FakeGPIO");

  auto ok = m_file.open(QIODevice::ReadWrite);
  if (!ok) {
    throw std::invalid_argument("bad file");
  }

  m_watcher.addPath(QString::fromStdString(watch_path));
  QFileSystemWatcher::connect(&m_watcher, &QFileSystemWatcher::fileChanged, [this]() {
    DLOG(INFO) << "Socket changed.";
    OnFileChange();
  });

}

void FakeGPIO::OnFileChange() {
  if (m_file.size() == 0) { return; }

  auto buffer = m_file.readAll();
  bool ok = false;
  auto pin = buffer.toUInt(&ok);
  if (!ok) {
    DLOG(ERROR) << "Invalid pin command - " << buffer.toStdString();
  } else {
// Ok we have a valid pin. What do we do with it?
//    auto x = m_signal_callback_map.find(pin);
//    if (x != m_signal_callback_map.end()) {
//      x->second(pin);
//    } else {
//      DLOG(INFO) << "We don't have a callback configured for pin(" << pin << ").";
//    }
  }

  m_file.resize(0);
}

FakeGPIO::~FakeGPIO() {
  // Are we leaking the m_watcher members and fds?
  DLOG(INFO) << "Disposing FakeGPIO";

  m_file.remove();
}
std::vector<GPIOPin> FakeGPIO::pins() const {
  return {
      m_pin
  };

}
GPIOPin FakeGPIO::pin(uint32_t index) const {
  if (index > 0) {
    throw "FIXME";
  }
  return m_pin;
}
void FakeGPIO::onPinChange(const GPIOPin &pin, std::function<void(bool)>) {
}

extern "C" FakeGPIO *create(const std::filesystem::path &path) {
  DLOG(INFO) << "Creating FakeGPIO";
  return new FakeGPIO(path);
}

} // gpio
