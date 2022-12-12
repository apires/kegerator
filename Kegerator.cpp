//
// Created by Antonio Jose Pires on 11/13/22.
//

#include <QRandomGenerator>
#include <QDir>
#include "Kegerator.hpp"

Kegerator::Kegerator() {
  m_configuration_screen.InitializeBody();
  m_soundboard_screen.InitializeBody();

  BindPlayerEvents();
  BindWindowEvents();

  m_configuration_screen.SetOnMenuButtonClick([this]() {
    m_configuration_screen.hide();
  });
  m_soundboard_screen.SetOnMenuButtonClick([this]() {
    ShowConfiguration();
  });

}

void Kegerator::ReloadTracks() {
  m_tracks.clear();
  for (auto &path : m_track_paths) {
    auto track = player::AudioTrack::SlurpDirectory(path);
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

void Kegerator::PlayTrack(const player::AudioTrack &t) {
  m_soundboard_screen.SetPlayerText(QString::fromStdString(t.GetDisplayString()));
  t.Play(m_player);
}

void Kegerator::ReloadButtons() {
  DLOG(INFO) << "Reloading Buttons";
  for (const auto &t : m_tracks) {
    DLOG(INFO) << "Found track " << t.GetDisplayString();
    auto b = new RoundButton(t.GetDisplayString());
    b->onClick = [&]() {
      PlayTrack(t);
    };
    m_soundboard_screen.AddButton(b);
  }

}

void Kegerator::BindPlayerEvents() {
  m_player.onProgress = [&](auto current, auto total) {
    m_soundboard_screen.Player().setSliderMaximum(total);
    m_soundboard_screen.Player().setSliderPosition(current);
  };
  m_player.onStart = [&]() {
    m_soundboard_screen.Player().show();
    m_soundboard_screen.Player().setStopButton();
  };
  m_player.onEnd = [&]() {
    m_soundboard_screen.Player().setSliderPosition(0);
    m_soundboard_screen.Player().setPlayButton();
    m_soundboard_screen.Player().hide();
  };
}

void Kegerator::BindWindowEvents() {
  m_soundboard_screen.onPlayButtonClick = [this]() {
    if (m_player.isPlaying()) {
      m_player.stop();
      m_soundboard_screen.Player().setPlayButton();
    } else {
      m_player.play();
      m_soundboard_screen.Player().setStopButton();
    }
  };
}
void Kegerator::AddTrackPath(const std::string &path) {
  m_track_paths.insert(path);
  ReloadTracks();
}

void Kegerator::ShowConfiguration() {
//  m_soundboard_screen.hide();
  m_configuration_screen.show();
}

void Kegerator::ShowSoundboard() {
//  m_configuration_screen.hide();
  m_soundboard_screen.show();
}
