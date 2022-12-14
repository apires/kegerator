//
// Created by Antonio Jose Pires on 12/8/22.
//

#include <QPushButton>
#include "ConfigurationScreen.hpp"
#include "../buttons/RoundButton.hpp"

namespace ui {

void ConfigurationScreen::AddOption(const QString &label, const std::function<void(void)> &onClick) {

  auto btn = new QPushButton(label, this);
  btn->setFont(QFont("Sans Serif, Apple Color Emoji", 48));
  QObject::connect(btn, &QPushButton::pressed, this, [onClick]() {
    if (onClick != nullptr) {
      onClick();
    }
  });

  body().layout()->addWidget(btn);
}

void ConfigurationScreen::InitializeBody() {
  KegeratorScreen::InitializeBody();
  body().setLayout(new FlowLayout());
}
void ConfigurationScreen::AddOption(QIcon icon, const std::function<void(void)> &onClick) {

  auto btn = new RoundButton(std::move(icon), "", this);
  QObject::connect(btn, &QPushButton::pressed, this, [onClick]() {
    if (onClick != nullptr) {
      onClick();
    }
  });
  body().layout()->addWidget(btn);
}

} // ui
