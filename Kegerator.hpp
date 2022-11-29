//
// Created by Antonio Jose Pires on 11/13/22.
//

#ifndef KEGERATOR_QT__KEGERATOR_HPP_
#define KEGERATOR_QT__KEGERATOR_HPP_

#include "glog/logging.h"
#include "player/Track.hpp"
#include "ui/MainWindow.hpp"
#include "ui/Player.hpp"
#include "ui/RoundButton.hpp"

class Kegerator {
 public:
  explicit Kegerator();
  void ReloadButtons();
  void PlayRandomTrack();
  void LoadTracks(const std::string &path);

  void show() { m_window.show(); };

 private:
  ui::MainWindow m_window;
  player::Player m_player;
  std::vector<player::Track> m_tracks;
  void BindWindowEvents();
  void BindPlayerEvents();

  void PlayTrack(const player::Track &t);
};

#endif // KEGERATOR_QT__KEGERATOR_HPP_
