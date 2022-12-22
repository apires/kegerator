//
// Created by Antonio Jose Pires on 11/13/22.
//

#ifndef KEGERATOR_QT_PLAYER_AUDIOTRACK_HPP_
#define KEGERATOR_QT_PLAYER_AUDIOTRACK_HPP_

#include "AudioPlayer.hpp"
#include <string>
namespace player {

class AudioTrack {
 public:
  explicit AudioTrack(const std::string &path) {
    m_path = path;
    probeMetadata();
  }

  static std::vector<AudioTrack> SlurpDirectory(const std::string &directory);

  [[nodiscard]] std::string GetArtist() const { return m_artist; }
  [[nodiscard]] std::string GetTitle() const { return m_title; }
  [[nodiscard]] std::string GetTrackName() const;

  friend std::ostream &operator<<(std::ostream &title, const player::AudioTrack &p);

  void Play(AudioPlayer &player) const;

 private:
  std::string m_path;
  std::string m_artist;
  std::string m_title;
  void probeMetadata();
};
} // namespace player
#endif // KEGERATOR_QT_PLAYER_AUDIOTRACK_HPP_
