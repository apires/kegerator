//
// Created by Antonio Jose Pires on 11/13/22.
//

#ifndef KEGERATOR_QT_UI_ROUNDBUTTON_HPP_
#define KEGERATOR_QT_UI_ROUNDBUTTON_HPP_

#include <QPushButton>

class RoundButton : public QPushButton {

public:
  RoundButton(const std::string &text, QWidget *parent);
  explicit RoundButton(const std::string &text);
  std::function<void()> onClick;
};

#endif // KEGERATOR_QT_UI_ROUNDBUTTON_HPP_
