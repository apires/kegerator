//
// Created by Antonio Jose Pires on 12/8/22.
//

#include "SoundboardScreen.hpp"

namespace ui {

void SoundboardScreen::InitializeBody() {
  KegeratorScreen::InitializeBody();
  body().setLayout(new FlowLayout());

  layout()->addWidget(&m_player);
  layout()->setAlignment(&m_player, Qt::AlignHCenter);
  m_player.setFixedWidth(width() / 2);
  m_player.onPlayButtonClick = [this]() {
    if (onPlayButtonClick) onPlayButtonClick();
  };
  m_player.hide();

}

}
