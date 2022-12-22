//
// Created by Antonio Jose Pires on 12/19/22.
//

#ifndef KEGERATOR_QT_UI_TOAST_HPP_
#define KEGERATOR_QT_UI_TOAST_HPP_

#include <QWidget>
#include <QString>
#include <QTimer>
#include <QVBoxLayout>

namespace ui {
class Toast {
 public:
  explicit Toast(QWidget *main_window);
  void ShowInfo(const QString &label);
  void ShowInfo(const QString &text, std::chrono::milliseconds duration);

 private:
  using tick = const std::chrono::milliseconds;

  QWidget m_widget;
  QVBoxLayout m_layout;
  QTimer m_timer;
  tick m_default_duration = tick(3000);
};

}

#endif //KEGERATOR_QT_UI_TOAST_HPP_
