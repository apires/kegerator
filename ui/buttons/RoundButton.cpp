//
// Created by Antonio Jose Pires on 11/13/22.
//

#include "RoundButton.hpp"
#include "glog/logging.h"

RoundButton::RoundButton(const std::string &text)
    : RoundButton(text, nullptr) {}

RoundButton::RoundButton(const std::string &text, QWidget *parent)
    : QPushButton(QString::fromStdString(text), parent) {
  setStyleSheet("QPushButton { "
                "width: 60px;"
                "height: 60px;"
                "border: 4px solid #107ABC;"
                "background-color: #FAFAFA;"
                "border-radius: 30px;"
                "}"
                "QPushButton:pressed {"
                "background-color: #F2F2F2;"
                "}");

  QObject::connect(this, &QPushButton::clicked, [this, text]() {
    if (onClick == nullptr) {
      DLOG(INFO) << "Button [" << text << "] does not have a click handler installed.";
      return;
    }
    onClick();
  });
}
