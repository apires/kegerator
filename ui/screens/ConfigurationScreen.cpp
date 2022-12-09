//
// Created by Antonio Jose Pires on 12/8/22.
//

#include <QPushButton>
#include "ConfigurationScreen.hpp"

namespace ui {
ConfigurationScreen::ConfigurationScreen(QWidget *parent) : QWidget(parent) {

  setMinimumSize(800, 600);
  setStyleSheet("background-color: white;");

  setLayout(&m_root_layout);

  m_button_grid.setLayout(&m_button_grid_layout);
  m_root_layout.addWidget(&m_button_grid, 1);

}

void ConfigurationScreen::AddOption(const QString &label, const std::function<void(void)> &onClick) {

  auto btn = new QPushButton(label, this);
  btn->setFont(QFont("Sans Serif, Apple Color Emoji", 48));
  QObject::connect(btn, &QPushButton::pressed, this, [onClick]() {
    if (onClick != nullptr) {
      onClick();
    }
  });

  m_button_grid_layout.addWidget(btn);
}

} // ui
