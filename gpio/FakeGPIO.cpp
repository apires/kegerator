//
// Created by Antonio Jose Pires on 11/18/22.
//

#include <QFile>
#include "FakeGPIO.hpp"
#include "glog/logging.h"

namespace gpio {

FakeGPIO::FakeGPIO() {
  m_file.setFileName("/tmp/socket.keg");
  auto ok = m_file.open(QIODevice::ReadWrite);
  if (!ok) {
    throw std::invalid_argument("bad file");
  }

  m_watcher.addPath("/tmp/socket.keg");
  QFileSystemWatcher::connect(&m_watcher, &QFileSystemWatcher::fileChanged, this, &FakeGPIO::OnFileChange);
}

void FakeGPIO::OnFileChange(const QString &path) {
  if (m_file.size() == 0) { return; }

  auto buffer = m_file.readAll();
  bool ok = false;
  auto pin = buffer.toInt(&ok);
  if (!ok) {
    DLOG(ERROR) << "Invalid pin command - " << buffer.toStdString();
  } else {
    // Ok we have a valid pin. What do we do with it?
    auto x = m_signal_callback_map.find(pin);
    if (x != m_signal_callback_map.end()) {
      x->second(pin);
    } else {
      DLOG(INFO) << "We don't have a callback configured for pin(" << pin << ").";
    }
  }

  m_file.resize(0);
}

void FakeGPIO::SetPinChangeCallback(u_int pin, std::function<void(u_int pin)> callback) {
  m_signal_callback_map.insert({pin, callback});
}

FakeGPIO::~FakeGPIO() {
  m_file.remove();
}

} // gpio