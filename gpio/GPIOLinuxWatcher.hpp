//
// Created by Antonio Jose Pires on 11/28/22.
//

#ifndef KEGERATOR_QT_GPIO_MAC_STUBS_GPIOLINUXWATCHER_HPP_
#define KEGERATOR_QT_GPIO_MAC_STUBS_GPIOLINUXWATCHER_HPP_

#include <QThread>

#ifdef __APPLE__
#include "mac_stubs/gpiod.h"
#endif
#ifdef  __linux__
#include "gpiod.h"
#endif

namespace gpio {

class GPIOLinuxWatcher : public QThread {
 Q_OBJECT
 protected:
  void run() override;
 public:
  explicit GPIOLinuxWatcher(QObject *parent, std::string path)
      : QThread(parent), m_path(std::move(path)) {}
  ~GPIOLinuxWatcher() override;

 public Q_SLOTS:
  void UpdatePins(std::vector<uint32_t> pins);

 Q_SIGNALS:
  void pinDepressed(uint32_t pin);

 private:
  std::vector<uint32_t> m_pins;
  std::string m_path;
  bool m_thread_closing = false;
  static int onPollEventRaised(unsigned int line_count,
                               gpiod_ctxless_event_poll_fd *descriptors,
                               const timespec *timeout,
                               void *watcher_ptr);
  static int onEdgeEventRaised(int event_type, unsigned int offset, const timespec *timestamp, void *watcher_ptr);
};

} // gpio

#endif //KEGERATOR_QT_GPIO_MAC_STUBS_GPIOLINUXWATCHER_HPP_
