//
// Created by Antonio Jose Pires on 11/28/22.
//

#include "LibGPIOdWatcher.hpp"
#include "glog/logging.h"
#include "poll.h"

namespace gpio {

void LibGPIOdWatcher::run() {
  auto ts = timespec{10, 0};
  LOG(INFO) << "Starting monitoring loop for GPIO";
  gpiod_ctxless_event_monitor_multiple(m_path.c_str(),
                                       GPIOD_CTXLESS_EVENT_RISING_EDGE,
                                       m_pins.data(),
                                       static_cast<unsigned int>(m_pins.size()),
                                       true, // PULL_UP?
                                       "Kegerator::LibGPIOd",
                                       &ts,
                                       &LibGPIOdWatcher::onPollEventRaised,
                                       &LibGPIOdWatcher::onEdgeEventRaised,
                                       this);
}

int LibGPIOdWatcher::onEdgeEventRaised(int event_type, // Always GPIOD_CTXLESS_EVENT_RISING_EDGE ?
                                       unsigned int offset, // GPIO pin
                                       const timespec *timestamp,
                                       void *watcher_ptr) {
  auto watcher = static_cast<LibGPIOdWatcher *>(watcher_ptr);
  emit watcher->pinDepressed(offset);
  if (watcher->m_thread_closing) {
    LOG(INFO) << "Done with the loop.";
    return GPIOD_CTXLESS_EVENT_CB_RET_STOP;
  } else {
    return GPIOD_CTXLESS_EVENT_CB_RET_OK;
  }
};

void LibGPIOdWatcher::UpdatePins(std::vector<uint32_t> pins) {
  m_thread_closing = true;
  this->quit();
  this->wait();

  m_pins = std::move(pins);

  m_thread_closing = false;
  this->start();
}

int LibGPIOdWatcher::onPollEventRaised(unsigned int num_lines,
                                       gpiod_ctxless_event_poll_fd *fds,
                                       const timespec *timeout,
                                       void *watcher_ptr) {

  auto watcher = static_cast<LibGPIOdWatcher *>(watcher_ptr);

  if (watcher->m_thread_closing) {
    LOG(INFO) << "Done with the loop.";
    return GPIOD_CTXLESS_EVENT_POLL_RET_STOP;
  }

  // Canonical implementation from libwhatever
  // we should be doing something more cpp-ey and modern-ey?
  auto poll_fds = new pollfd[GPIOD_LINE_BULK_MAX_LINES];
  unsigned int i;
  int rv, ret;

  if (num_lines > GPIOD_LINE_BULK_MAX_LINES)
    return GPIOD_CTXLESS_EVENT_POLL_RET_ERR;

  for (i = 0; i < num_lines; i++) {
    poll_fds[i].fd = fds[i].fd;
    poll_fds[i].events = POLLIN | POLLPRI;
  }

#ifdef __linux__
  rv = ppoll(poll_fds, num_lines, timeout, NULL);
#endif
#ifdef __APPLE__
  rv = poll(poll_fds, num_lines, static_cast<int>(timeout->tv_nsec));
#endif
  if (rv < 0) {
    if (errno == EINTR)
      return GPIOD_CTXLESS_EVENT_POLL_RET_TIMEOUT;
    else
      return GPIOD_CTXLESS_EVENT_POLL_RET_ERR;
  } else if (rv == 0) {
    return GPIOD_CTXLESS_EVENT_POLL_RET_TIMEOUT;
  }

  ret = rv;
  for (i = 0; i < num_lines; i++) {
    if (poll_fds[i].revents) {
      fds[i].event = true;
      if (!--rv)
        break;
    }
  }

  return ret;
}

LibGPIOdWatcher::~LibGPIOdWatcher() {
  m_thread_closing = true;
  this->quit();
  this->wait();
}
} // gpio
