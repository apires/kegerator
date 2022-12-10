//
// Created by Antonio Jose Pires on 12/8/22.
//

#include "KegeratorScreen.hpp"

#include <QLabel>

namespace ui {

KegeratorScreen::KegeratorScreen(QWidget *parent) : QWidget(parent) {
  setMinimumSize(800, 600);

  InitializeHeader();

  setLayout(new QVBoxLayout());
  layout()->setContentsMargins(0, 0, 0, 0);
  layout()->setAlignment(Qt::AlignTop);

  layout()->addWidget(&m_header);
  layout()->addWidget(&m_body);
}

void KegeratorScreen::InitializeHeader() {
  // TODO: This should be like a heading or something?
  auto spacer = new QWidget(this);
  spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  m_header.setLayout(new QHBoxLayout());
  m_header.layout()->addWidget(spacer);
  m_header.layout()->addWidget(&m_menu_button);
  m_header.layout()->setAlignment(&m_menu_button, Qt::AlignRight);
  m_menu_button.setStyleSheet(R"(
    QPushButton {
      font-size: 26px;
      border: 1px solid lightgray;
      background: white;
      border-radius: 4px;
    }
  )");
  m_menu_button.setFixedSize(38, 38);
  SetMenuIcon(MenuIcon::Hamburger);
}

void KegeratorScreen::SetMenuIcon(MenuIcon icon) {
  m_menu_button.setText(getMenuIconRepresentation(icon));
}

QString KegeratorScreen::getMenuIconRepresentation(MenuIcon icon) {
  switch (icon) {
    case Hamburger: {
      return "≡";
    }
    case X: {
      return "X";
    }
  }
}

void KegeratorScreen::InitializeBody() {
  m_body.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  m_body.setStyleSheet("background-color: lightblue");
}

QWidget &KegeratorScreen::body() {
  return m_body;
}

}
