//
// Created by Antonio Jose Pires on 11/13/22.
//

#ifndef KEGERATOR_QT__KEGERATOR_HPP_
#define KEGERATOR_QT__KEGERATOR_HPP_

#include <set>
#include "glog/logging.h"
#include "player/Track.hpp"
#include "ui/MainWindow.hpp"
#include "ui/Player.hpp"
#include "ui/buttons/RoundButton.hpp"

class Kegerator {
 public:
  explicit Kegerator();
  void ReloadButtons();
  void PlayRandomTrack();
  void AddTrackPath(const std::string &);
  void ReloadTracks();

  void show() { m_window.show(); }

 private:
  ui::MainWindow m_window;
  player::Player m_player;

  std::set<std::string> m_track_paths;
  std::vector<player::Track> m_tracks;

  void BindWindowEvents();
  void BindPlayerEvents();

  void PlayTrack(const player::Track &t);
};

#endif // KEGERATOR_QT__KEGERATOR_HPP_
