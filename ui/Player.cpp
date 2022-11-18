//
// Created by Antonio Jose Pires on 11/13/22.
//

#include "Player.hpp"

Player::Player(QWidget *parent)
    : QWidget(parent, Qt::WindowFlags::enum_type::Widget) {

  setLayout(reinterpret_cast<QLayout *>(&m_layout));

  setStyleSheet("background-color: white; padding: 6px; border-radius: 6px;");
  m_button.setStyleSheet("font-size: 24px");

  m_slider.setOrientation(Qt::Orientation::Horizontal);
  m_slider.setAttribute(Qt::WidgetAttribute::WA_TransparentForMouseEvents);
  m_button.setText(STOP_ICON);

  m_layout.addWidget(&m_slider);
  m_layout.addWidget(&m_button);

  QObject::connect(&m_button, &QPushButton::clicked, [this]() {
    onPlayButtonClick();
  });
}

void Player::setStopButton() { m_button.setText(STOP_ICON); }
void Player::setPlayButton() { m_button.setText(PLAY_ICON); }
void Player::setSliderMaximum(int max) { m_slider.setMaximum(max); }
void Player::setSliderPosition(int pos) { m_slider.setSliderPosition(pos); }