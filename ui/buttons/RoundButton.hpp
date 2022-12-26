//
// Created by Antonio Jose Pires on 11/13/22.
//

#ifndef KEGERATOR_QT_UI_ROUNDBUTTON_HPP_
#define KEGERATOR_QT_UI_ROUNDBUTTON_HPP_

#include <QPushButton>

class RoundButton : public QPushButton {

 public:
  explicit RoundButton(const QString &text, QWidget *parent);
  explicit RoundButton(const std::string &text, QWidget *parent);
  explicit RoundButton(QIcon icon, const QString &text, QWidget *parent);
  std::function<void()> onClick;
  void SetColor(QColor color);
};

#endif // KEGERATOR_QT_UI_ROUNDBUTTON_HPP_
