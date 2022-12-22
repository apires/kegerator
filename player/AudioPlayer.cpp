//
// Created by Antonio Jose Pires on 11/13/22.
//

#include "AudioPlayer.hpp"
#include "AudioTrack.hpp"

namespace player {

AudioPlayer::AudioPlayer() : m_output(), m_player() {

  QObject::connect(&m_player, &QMediaPlayer::durationChanged,
                   [&](const qint64 newDuration) { m_duration = newDuration; });

  QObject::connect(&m_player, &QMediaPlayer::positionChanged,
                   [&](const qint64 newPosition) {
                     if (onProgress != nullptr) {
                       onProgress(newPosition, m_duration);
                     }
                   });

  QObject::connect(&m_player, &QMediaPlayer::mediaStatusChanged,
                   [&](const auto status) {
                     if (status == QMediaPlayer::MediaStatus::EndOfMedia) {
                       if (onProgress)
                         onProgress(m_duration, m_duration);
                       if (onEnd)
                         onEnd();
                     }
                   });

  QObject::connect(&m_player, &QMediaPlayer::errorOccurred,
                   [&](QMediaPlayer::Error error, const QString &errorString) {
                     DLOG(ERROR) << errorString.toStdString();
                   });

  m_player.setAudioOutput(&m_output);
  m_player.play();

}

void AudioPlayer::setSource(const std::filesystem::path &path) {
  m_player.setSource(QUrl::fromLocalFile(QString::fromStdString(path)));
}
void AudioPlayer::play() {
  if (onStart) onStart();
  m_player.play();
}

void AudioPlayer::stop() {
  if (onEnd) onEnd();
  m_player.stop();
}
bool AudioPlayer::isPlaying() {
  return m_player.playbackState() == QMediaPlayer::PlaybackState::PlayingState;
}

} // namespace player
