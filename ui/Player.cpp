//
// Created by Antonio Jose Pires on 11/13/22.
//

#include "Player.hpp"
#include "glog/logging.h"

namespace ui {
Player::Player(QWidget *parent)
    : QWidget(parent, Qt::WindowFlags::enum_type::Widget) {

  setLayout(&m_layout);
  setStyleSheet("background-color: white; border-radius: 6px;");

  InitializePlayerControls();
  InitializeMetadataSection();

  m_layout.addWidget(&m_metadata);
  m_layout.addWidget(&m_player_control);

  setVisible(false);
}

void Player::InitializeMetadataSection() {
  m_metadata.setLayout(&m_metadata_layout);

  m_metadata_label.setAlignment(Qt::Alignment::enum_type::AlignCenter);
  m_metadata_layout.addWidget(&m_metadata_label);
}

void Player::InitializePlayerControls() {

  m_player_control.setLayout(&m_player_control_layout);
  m_player_control_layout.addWidget(&m_slider);
  m_player_control_layout.addWidget(&m_button);

  m_slider.setOrientation(Qt::Orientation::Horizontal);
  m_slider.setAttribute(Qt::WidgetAttribute::WA_TransparentForMouseEvents);

  m_button.setText(STOP_ICON);
  m_button.setStyleSheet("font-size: 24px");

  QObject::connect(&m_button, &QPushButton::clicked, [this]() {
    onPlayButtonClick();
  });
}

void Player::setStopButton() { m_button.setText(STOP_ICON); }
void Player::setPlayButton() { m_button.setText(PLAY_ICON); }
void Player::setSliderMaximum(int max) { m_slider.setMaximum(max); }
void Player::setSliderPosition(int pos) { m_slider.setSliderPosition(pos); }
void Player::setPlayerText(const QString &label) {
  m_metadata_label.setText(label);
}
void Player::showEvent(QShowEvent *event) {
  if (m_metadata_label.text().isEmpty()) {
    m_metadata.hide();
  } else {
    m_metadata.show();
  }
}
}
