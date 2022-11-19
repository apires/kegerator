//
// Created by Antonio Jose Pires on 11/13/22.
//

#ifndef KEGERATOR_QT_PLAYER_TRACK_HPP_
#define KEGERATOR_QT_PLAYER_TRACK_HPP_

#include "Player.hpp"
#include <QMediaPlayer>
#include <string>
namespace player {

class Track {
 public:
  explicit Track(const std::string &path) {
    m_path = path;
    probeMetadata();
  }

  static std::vector<Track> SlurpDirectory(const std::string &directory);

  [[nodiscard]] std::string GetArtist() const { return m_artist; }
  [[nodiscard]] std::string GetTitle() const { return m_title; }
  [[nodiscard]] std::string GetDisplayString() const;

  void Play(const std::shared_ptr<player::Player> &player) const;

 private:
  std::string m_path;
  std::string m_artist;
  std::string m_title;

  void probeMetadata();

};
} // namespace player
#endif // KEGERATOR_QT_PLAYER_TRACK_HPP_
