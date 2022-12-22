//
// Created by Antonio Jose Pires on 12/19/22.
//

#include "Toast.hpp"
#include "glog/logging.h"
#include <QLabel>

namespace ui {

void Toast::ShowInfo(const QString &text) { ShowInfo(text, m_default_duration); }
void Toast::ShowInfo(const QString &text, std::chrono::milliseconds duration) {
  if (m_timer.isActive()) {
    LOG(INFO) << "We don't really know how to show multiple toasts atm...";
    return;
  }
  DLOG(INFO) << "Toasting";

  auto label = new QLabel(text);
  label->setAlignment(Qt::AlignCenter);
  label->setObjectName("toast_message");
  label->setWordWrap(true);

  m_layout.addWidget(label);
  m_widget.adjustSize();

  auto parent = dynamic_cast<QWidget *>(m_widget.parent());

  // position bottom right, but maybe 10 px from the border
  m_widget.move(parent->width() - m_widget.width() - 10, parent->height() - m_widget.height() - 10);

  QObject::connect(&m_timer, &QTimer::timeout, [&, label, duration]() {
    DLOG(INFO) << "Toast: "
               << duration.count() * tick::period::num / tick::period::den
               << " ms timer is over, cleaning up.";
    // TODO: Use QPropertyAnimation and an opacity transition here w/ a open time transition-long timer to
    //       dispose to the toast.
    m_widget.hide();
    m_layout.removeWidget(label);
    delete label;
  });

  m_widget.show();
  m_timer.start(duration);
}

Toast::Toast(QWidget *main_window) : m_widget(main_window), m_layout(&m_widget) {

  m_widget.hide();
  m_widget.setObjectName("toast");
  m_widget.setFixedSize(200, 80);
  m_widget.setStyleSheet(R"(
    #toast {
      background-color: white;
      border: 1px solid lightgray;
      border-radius: 6px;
      padding: 10px;
    }
    #toast #toast_message {
      font-size: 16px;
    }
  )");
  m_widget.setLayout(&m_layout);
  m_timer.setSingleShot(true);
}

}
