//
// Created by Antonio Jose Pires on 11/13/22.
//

#ifndef KEGERATOR_QT_PLAYER_AUDIOPLAYER_HPP_
#define KEGERATOR_QT_PLAYER_AUDIOPLAYER_HPP_

#include "glog/logging.h"
#include <QAudioOutput>
#include <QMediaPlayer>
#include <filesystem>

namespace player {

class AudioPlayer {
 public:
  explicit AudioPlayer();
  void setSource(const std::filesystem::path &path);
  void play();
  void stop();
  bool isPlaying();

  std::function<void(qint64 current, qint64 duration)> onProgress;
  std::function<void()> onStart;
  std::function<void()> onEnd;

  // private
 private:
  QAudioOutput m_output;
  QMediaPlayer m_player;
  qint64 m_duration;
};

} // namespace player

#endif // KEGERATOR_QT_PLAYER_AUDIOPLAYER_HPP_
