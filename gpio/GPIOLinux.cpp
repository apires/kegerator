//
// Created by Antonio Jose Pires on 11/28/22.
//

#include <string>
#include <glog/logging.h>
#include "GPIOLinux.hpp"

namespace gpio {

GPIOLinux::GPIOLinux(std::string path)
    : m_watcher(new GPIOLinuxWatcher(this, std::move(path))) {
  LOG(INFO) << "GPIOLinux short constructor";

  m_watcher->start();
  QObject::connect(m_watcher, &gpio::GPIOLinuxWatcher::pinDepressed, this,
                   [&](uint32_t pin) {
                     auto x = m_signal_callback_map.find(pin);
                     if (x != m_signal_callback_map.end()) {
                       DLOG(INFO) << "Boom" << x->first;
                       x->second(pin);
                     } else {
                       DLOG(INFO) << "We don't have a callback configured for pin(" << pin << ").";
                     }
                   });
}

GPIOLinux::GPIOLinux(std::string path, std::vector<uint32_t> pins) : GPIOLinux(std::move(path)) {
  LOG(INFO) << "GPIOLinux long constructor";
  m_watcher->UpdatePins(std::move(pins));
}
} // gpio
