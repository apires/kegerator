//
// Created by Antonio Jose Pires on 11/13/22.
//

#include <QRandomGenerator>
#include "RoundButton.hpp"
#include "glog/logging.h"

void RoundButton::SetColor(QColor color) {
  auto border = QColor();
  auto pressed = QColor();
  border.setHsl(color.hue(), color.hslSaturation(), color.lightness() - 76);
  pressed.setHsl(color.hue(), color.hslSaturation() - 80, color.lightness());

  setStyleSheet(QString(R"(QPushButton {
                      width: 60px;
                      height: 60px;
                      font-size: 24px;
                      border: 4px solid %1;
                      background-color: %2;
                      border-radius: 30px;
                    }
                    QPushButton:pressed {
                      background-color: %3;
                    }
  )").arg(border.name(), color.name(), pressed.name()));
}

RoundButton::RoundButton(const QString &text, QWidget *parent = nullptr)
    : QPushButton(text, parent) {
  setStyleSheet(R"(QPushButton {
                      width: 60px;
                      height: 60px;
                      font-size: 24px;
                      border: 4px solid #107ABC;
                      background-color: #FAFAFA;
                      border-radius: 30px;
                    }
                    QPushButton:pressed {
                      background-color: #F2F2F2;
                    }
  )");

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
  setStyleSheet(R"(QPushButton {
                      width: 60px;
                      height: 60px;
                      qproperty-iconSize: 36px;
                      border: 4px solid darkgrey;
                      background-color: #FAFAFA;
                      border-radius: 30px;
                    }
                    QPushButton:pressed {
                      background-color: #F2F2F2;
                    }
  )");

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