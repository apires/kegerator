//
// Created by Antonio Jose Pires on 11/13/22.
//

#include "AudioTrack.hpp"
#include "AudioPlayer.hpp"
#include "glog/logging.h"
#include <QDir>
#include <QMediaPlayer>
#include <QtCore>
#include <QMediaMetaData>

namespace player {

void AudioTrack::probeMetadata() {

  QMediaPlayer player;
  QEventLoop loop;

  QObject::connect(
      &player, &QMediaPlayer::metaDataChanged, &loop, &QEventLoop::quit
  );
  player.setSource(QUrl::fromLocalFile(QString::fromStdString(m_path)));

  // Lookup is async, so we spawn an event loop to wait for that to be over before we have values
  loop.exec();

  auto metadata = player.metaData();
  // There's an artist key, but for some reason QT seems to pick up
  // what ffprobe calls "artist" as ContributingArtist?
  if (!metadata[QMediaMetaData::Key::ContributingArtist].isNull()) {
    m_artist = metadata[QMediaMetaData::Key::ContributingArtist].toString().toStdString();
  } else {
    m_artist = "Unknown Artist";
  }

  if (!metadata[QMediaMetaData::Key::Title].isNull()) {
    m_title = metadata[QMediaMetaData::Key::Title].toString().toStdString();
  } else {
    m_title = "Unknown Title";
  }

}

std::vector<AudioTrack> AudioTrack::SlurpDirectory(const std::string &s_directory) {
  auto dir = new QDir(QString::fromStdString((s_directory)));
  auto tracks = std::vector<AudioTrack>();

  for (const auto &entry : dir->entryList(QDir::Filters::enum_type::Files)) {
    auto p = dir->absolutePath().toStdString() + "/" + entry.toStdString();
    tracks.emplace_back(p);
  }

  return tracks;
}
void AudioTrack::Play(AudioPlayer &player) const {
  player.setSource(m_path);
  player.play();
}

const std::string AudioTrack::GetDisplayString() const {
  auto title = std::stringstream();

  if (!GetArtist().empty() && !GetTitle().empty()) {
    title << GetArtist() << " - " << GetTitle();
  } else if (GetArtist().empty() && !GetTitle().empty()) {
    title << GetTitle();
  } else if (!GetArtist().empty() && GetTitle().empty()) {
    // If we only have an artist, what do we do?
    title << "Something by " << GetArtist();
  }
  return title.str();
}

} // namespace player