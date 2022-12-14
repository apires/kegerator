//
// Created by Antonio Jose Pires on 11/13/22.
//

#include "RoundButton.hpp"
#include "glog/logging.h"

RoundButton::RoundButton(const QString &text, QWidget *parent = nullptr)
    : QPushButton(text, parent) {
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
      DLOG(INFO) << "Button [" << text.toStdString() << "] does not have a click handler installed.";
      return;
    }
    onClick();
  });
}

RoundButton::RoundButton(QIcon icon, const QString &text, QWidget *parent = nullptr)
    : QPushButton(icon, text, parent) {
  setStyleSheet("QPushButton { "
                "width: 60px;"
                "height: 60px;"
                "qproperty-iconSize: 36px;"
                "background-color: #FAFAFA;"
                "border: 4px solid darkgray;"
                "border-radius: 30px;"
                "}"
                "QPushButton:pressed {"
                "background-color: #F2F2F2;"
                "}");

  QObject::connect(this, &QPushButton::clicked, [this, text]() {
    if (onClick == nullptr) {
      DLOG(INFO) << "Button(icon) ['" << text.toStdString() << "'] does not have a click handler installed.";
      return;
    }
    onClick();
  });

}
RoundButton::RoundButton(const std::string &text, QWidget *parent = nullptr)
    : RoundButton(QString::fromStdString(text), parent) {}
