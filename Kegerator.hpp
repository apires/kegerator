//
// Created by Antonio Jose Pires on 11/13/22.
//

#ifndef KEGERATOR_QT__KEGERATOR_HPP_
#define KEGERATOR_QT__KEGERATOR_HPP_

#include <set>
#include "glog/logging.h"
#include "player/AudioTrack.hpp"
#include "ui/Player.hpp"
#include "ui/buttons/RoundButton.hpp"
#include "ui/screens/SoundboardScreen.hpp"
#include "ui/screens/ConfigurationScreen.hpp"

class Kegerator {
 public:
  explicit Kegerator();
  void ReloadButtons();
  void PlayRandomTrack();
  void AddTrackPath(const std::string &);
  void ReloadTracks();

  void ShowSoundboard();
  void ShowConfiguration();

 private:
  ui::ConfigurationScreen m_configuration_screen;
  ui::SoundboardScreen m_soundboard_screen;
  player::AudioPlayer m_player;

  std::set<std::string> m_track_paths;
  std::vector<player::AudioTrack> m_tracks;

  void BindWindowEvents();
  void BindPlayerEvents();

  void PlayTrack(const player::AudioTrack &t);
};

#endif // KEGERATOR_QT__KEGERATOR_HPP_
