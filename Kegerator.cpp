//
// Created by Antonio Jose Pires on 11/13/22.
//

#include "Kegerator.hpp"

Kegerator::Kegerator() {
  m_window = std::make_unique<ui::MainWindow>();
  m_player = std::make_shared<player::Player>();

  BindPlayerEvents();
  BindWindowEvents();
}

void Kegerator::LoadTracks(const std::string &path) {
  m_tracks = player::Track::SlurpDirectory(path);
  ReloadButtons();
}

void Kegerator::ReloadButtons() {

  for (const auto &t : m_tracks) {
    auto b = new RoundButton(t.GetTitle());
    b->onClick = [&]() { t.Play(m_player); };
    m_window->AddButton(b);
  }
  
}

void Kegerator::BindPlayerEvents() {
  m_player->onProgress = [&](auto current, auto total) {
    m_window->setSliderMaximum(total);
    m_window->setSliderPosition(current);
  };
  m_player->onStart = [&]() {
    m_window->ShowPlayer();
    m_window->setStopButton();
  };
  m_player->onEnd = [&]() {
    m_window->setSliderPosition(0);
    m_window->setPlayButton();
    m_window->HidePlayer();
  };
}

void Kegerator::BindWindowEvents() {
  m_window->onPlayButtonClick = [this]() {
    if (m_player->isPlaying()) {
      m_player->stop();
      m_window->setPlayButton();
    } else {
      m_player->play();
      m_window->setStopButton();
    }
  };
}
