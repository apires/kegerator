//
// Created by Antonio Jose Pires on 11/13/22.
//

#include <QRandomGenerator>
#include <QDir>
#include <QFileDialog>
#include "Kegerator.hpp"
#include "ui/Toast.hpp"
#include "ui/color/ColorPicker.hpp"

Kegerator::Kegerator() {
  BindPlayerEvents();
  BindWindowEvents();

  BuildConfigurationMenu();

  m_window.show();
}

void Kegerator::ReloadTracks() {
  m_tracks.clear();
  for (auto &path : m_track_paths) {
    auto track = player::AudioTrack::SlurpDirectory(path);
    DLOG(INFO) << "Loading track path from " << path;
    std::move(track.begin(), track.end(), std::back_inserter(m_tracks));
  }
  m_window.toast()->ShowInfo(QString("Loaded %1 track%2.")
                                 .arg(m_tracks.size())
                                 .arg(m_tracks.size() == 1 ? "" : "s"));

  ReloadButtons();
}

void Kegerator::PlayRandomTrack() {
  auto selection = QRandomGenerator::global()->bounded(static_cast<quint64>(m_tracks.size()));
  auto track = m_tracks.at(selection);
  PlayTrack(track);
}

void Kegerator::PlayTrack(const player::AudioTrack &t) {
  m_window.soundboard()->SetPlayerText(QString::fromStdString(t.GetTrackName()));
  t.Play(m_player);
}

QString Kegerator::getSoundboardButtonLabel(const player::AudioTrack &t) {

  if (!t.GetArtist().empty() && !t.GetTitle().empty()) {
    return QString("%1%2").arg(t.GetArtist()[0]).arg(t.GetTitle()[0]);
  }
  if (t.GetArtist().empty() && !t.GetTitle().empty()) {
    return QString::fromStdString(t.GetTitle().substr(0, 2));
  }
  if (!t.GetArtist().empty() && t.GetTitle().empty()) {
    // If we only have an artist, what do we do?
    return QString::fromStdString(t.GetTitle().substr(0, 2));
  }
  return {"NADA"};
}

void Kegerator::ReloadButtons() {
  DLOG(INFO) << "Reloading Buttons";
  for (const auto &t : m_tracks) {
    DLOG(INFO) << "Found track " << t;
    auto b = new RoundButton(getSoundboardButtonLabel(t), nullptr);
    b->onClick = [&]() { PlayTrack(t); };
    b->SetColor(ui::ColorPicker::forPath(t.GetPath()));
    m_window.soundboard()->AddButton(b);
  }

}

void Kegerator::BindPlayerEvents() {
  m_player.onProgress = [&](auto current, auto total) {
    m_window.soundboard()->Player().setSliderMaximum(total);
    m_window.soundboard()->Player().setSliderPosition(current);
  };
  m_player.onStart = [&]() {
    m_window.soundboard()->Player().show();
    m_window.soundboard()->Player().setStopButton();
  };
  m_player.onEnd = [&]() {
    m_window.soundboard()->Player().setSliderPosition(0);
    m_window.soundboard()->Player().setPlayButton();
    m_window.soundboard()->Player().hide();
  };
}

void Kegerator::BindWindowEvents() {
  m_window.soundboard()->onPlayButtonClick = [this]() {
    if (m_player.isPlaying()) {
      m_player.stop();
      m_window.soundboard()->Player().setPlayButton();
    } else {
      m_player.play();
      m_window.soundboard()->Player().setStopButton();
    }
  };
}
void Kegerator::AddTrackPath(const std::string &path) {
  m_track_paths.insert(path);
  ReloadTracks();
}

void Kegerator::BuildConfigurationMenu() {
  auto configuration = m_window.configuration();

  configuration->AddOption(QIcon(":kegerator/svg/open-folder-audio.svg"), [&]() -> void {
    auto path = QFileDialog::getExistingDirectory(nullptr,
                                                  "Select Import Path",
                                                  QDir::homePath(),
                                                  QFileDialog::Options::enum_type::ReadOnly
                                                      | QFileDialog::Options::enum_type::ShowDirsOnly);
    AddTrackPath(path.toStdString());
  });

}
