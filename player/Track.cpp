//
// Created by Antonio Jose Pires on 11/13/22.
//

#include "Track.hpp"
#include "Player.hpp"
#include "glog/logging.h"
#include <QDir>
#include <QMediaPlayer>
#include <QtCore>

namespace player {

void Track::probeMetadata() {

  QMediaPlayer player;
  QEventLoop loop;

  QObject::connect(
      &player, &QMediaPlayer::metaDataChanged, &loop, &QEventLoop::quit
  );

  player.setSource(QUrl::fromLocalFile(QString::fromStdString(m_path)));

  // Lookup is async, so we spawn an event loop to wait for that to be over before we have values
  loop.exec();

  auto metadata = player.metaData();

  if (!metadata[QMediaMetaData::Key::AlbumArtist].isNull()) {
    m_artist = metadata[QMediaMetaData::Key::AlbumArtist].toString().toStdString();
  } else {
    m_artist = "Unknown Artist";
  }

  if (!metadata[QMediaMetaData::Key::Title].isNull()) {
    m_title = metadata[QMediaMetaData::Key::Title].toString().toStdString();
  } else {
    m_title = "Unknown Title";
  }

}

std::vector<Track> Track::SlurpDirectory(const std::string &s_directory) {
  auto dir = new QDir(QString::fromStdString((s_directory)));
  auto tracks = std::vector<Track>();

  for (const auto &entry : dir->entryList(QDir::Filters::enum_type::Files)) {
    auto p = dir->absolutePath().toStdString() + "/" + entry.toStdString();
    tracks.emplace_back(p);
  }

  return tracks;
}
void Track::Play(const std::shared_ptr<Player> &player) const {
  player->setSource(m_path);
  player->play();

}
} // namespace player