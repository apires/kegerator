//
// Created by Antonio Jose Pires on 12/8/22.
//

#include "KegeratorScreen.hpp"
#include "glog/logging.h"
#include <QLabel>
#include <QIcon>
#include <QDirIterator>
#include <QHBoxLayout>

namespace ui {

KegeratorScreen::KegeratorScreen(QWidget *parent) : QWidget(parent) {

  InitializeHeader();

  setLayout(&m_layout);

  m_layout.setContentsMargins(0, 0, 0, 0);
  m_layout.setAlignment(Qt::AlignTop);

  m_layout.addWidget(&m_header);
  m_layout.addWidget(&m_body);

  setObjectName("rootWindow");
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
  QObject::connect(&m_menu_button, &QPushButton::pressed, this, [this]() {
    if (onMenuButtonClick != nullptr) {
      onMenuButtonClick();
    } else {
      DLOG(INFO) << "No menu button handler installed";
    }
  });
}

void KegeratorScreen::SetMenuIcon(MenuIcon icon) {
  m_menu_button.setIcon(getMenuIconRepresentation(icon));
}

QIcon KegeratorScreen::getMenuIconRepresentation(MenuIcon icon) {
  switch (icon) {
    case Grid: {
      return QIcon(":kegerator/svg/grid-menu.svg");
    }
    case X: {
      return QIcon(":kegerator/svg/close.svg");
    }
  }
  throw std::runtime_error("Invalid icon enum passed in to getMenuIconRepresentation");
}

void KegeratorScreen::InitializeBody() {
  m_body.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  m_body.setStyleSheet("background-color: transparent");
}

QWidget &KegeratorScreen::body() {
  return m_body;
}
void KegeratorScreen::SetOnMenuButtonClick(const std::function<void()> &on_menu_button_click) {
  onMenuButtonClick = on_menu_button_click;
}

}
