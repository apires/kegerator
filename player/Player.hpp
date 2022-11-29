//
// Created by Antonio Jose Pires on 11/13/22.
//

#ifndef KEGERATOR_QT_PLAYER_PLAYER_HPP_
#define KEGERATOR_QT_PLAYER_PLAYER_HPP_

#include "glog/logging.h"
#include <QAudioOutput>
#include <QMediaPlayer>

namespace player {

class Player {
 public:
  explicit Player();
  void setSource(const std::string &path);
  void play();
  void stop();
  bool isPlaying() { return m_player->playbackState() == QMediaPlayer::PlaybackState::PlayingState; }

  std::function<void(qint64 current, qint64 duration)> onProgress;
  std::function<void()> onStart;
  std::function<void()> onEnd;

  // private
 private:
  std::unique_ptr<QMediaPlayer> m_player;
  std::unique_ptr<QAudioOutput> m_output;
  qint64 m_duration;
};

} // namespace player

#endif // KEGERATOR_QT_PLAYER_PLAYER_HPP_
