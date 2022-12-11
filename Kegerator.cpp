//
// Created by Antonio Jose Pires on 11/13/22.
//

#include <QRandomGenerator>
#include <QDir>
#include "Kegerator.hpp"

Kegerator::Kegerator() : m_window(), m_player() {
  BindPlayerEvents();
  BindWindowEvents();
}

void Kegerator::ReloadTracks() {
  m_tracks.clear();
  for (auto &path : m_track_paths) {
    auto track = player::Track::SlurpDirectory(path);
    DLOG(INFO) << "Loading track path from " << path;
    std::move(track.begin(), track.end(), std::back_inserter(m_tracks));
  }
  ReloadButtons();
}

void Kegerator::PlayRandomTrack() {
  auto selection = QRandomGenerator::global()->bounded(static_cast<quint64>(m_tracks.size()));
  auto track = m_tracks.at(selection);
  PlayTrack(track);
}

void Kegerator::PlayTrack(const player::Track &t) {
  m_window.SetPlayerText(QString::fromStdString(t.GetDisplayString()));
  t.Play(m_player);
}

void Kegerator::ReloadButtons() {

  for (const auto &t : m_tracks) {
    DLOG(INFO) << "Found track " << t.GetDisplayString();
    auto b = new RoundButton(t.GetDisplayString());
    b->onClick = [&]() {
      PlayTrack(t);
    };
    m_window.AddButton(b);
  }

}

void Kegerator::BindPlayerEvents() {
  m_player.onProgress = [&](auto current, auto total) {
    m_window.setSliderMaximum(total);
    m_window.setSliderPosition(current);
  };
  m_player.onStart = [&]() {
    m_window.ShowPlayer();
    m_window.setStopButton();
  };
  m_player.onEnd = [&]() {
    m_window.setSliderPosition(0);
    m_window.setPlayButton();
    m_window.HidePlayer();
  };
}

void Kegerator::BindWindowEvents() {
  m_window.onPlayButtonClick = [this]() {
    if (m_player.isPlaying()) {
      m_player.stop();
      m_window.setPlayButton();
    } else {
      m_player.play();
      m_window.setStopButton();
    }
  };
}
void Kegerator::AddTrackPath(const std::string &path) {
  m_track_paths.insert(path);
  ReloadTracks();
}

void Kegerator::ShowSoundboard() {
  m_soundboard_screen.hide();
  m_configuration_screen.show();
}

void Kegerator::ShowConfiguration() {
  m_soundboard_screen.hide();
  m_configuration_screen.show();
}
