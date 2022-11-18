//
// Created by Antonio Jose Pires on 11/13/22.
//

#include "Player.hpp"

namespace player {
Player::Player() {

  m_output = std::make_unique<QAudioOutput>();
  m_player = std::make_unique<QMediaPlayer>();
  m_player->setAudioOutput(m_output.get());

  // Do we need to delete these signals, or do they go away when the players get
  // disposed?
  QObject::connect(m_player.get(), &QMediaPlayer::durationChanged,
                   [&](const qint64 newDuration) { m_duration = newDuration; });

  QObject::connect(m_player.get(), &QMediaPlayer::positionChanged,
                   [&](const qint64 newPosition) {
                     if (onProgress != nullptr) {
                       onProgress(newPosition, m_duration);
                     }
                   });

  QObject::connect(m_player.get(), &QMediaPlayer::mediaStatusChanged,
                   [&](const auto status) {
                     if (status == QMediaPlayer::MediaStatus::EndOfMedia) {
                       if (onProgress)
                         onProgress(m_duration, m_duration);
                       if (onEnd)
                         onEnd();
                     }
                   });
}
void Player::setSource(const std::string &path) {
  m_player->setSource(QUrl::fromLocalFile(QString::fromStdString(path)));
}
void Player::play() {
  if (onStart)
    onStart();
  m_player->play();
}

void Player::stop() {
  if (onEnd)
    onEnd();
  m_player->stop();
}

} // namespace player