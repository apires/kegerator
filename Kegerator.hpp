//
// Created by Antonio Jose Pires on 11/13/22.
//

#ifndef KEGERATOR_QT__KEGERATOR_HPP_
#define KEGERATOR_QT__KEGERATOR_HPP_

#include "glog/logging.h"
#include "lib/FlowLayout.hpp"
#include "player/Track.hpp"
#include "ui/MainWindow.hpp"
#include "ui/Player.hpp"
#include "ui/RoundButton.hpp"

class Kegerator {
 public:
  explicit Kegerator();
  void ReloadButtons();
  void LoadTracks(const std::string &path);

  void show() { m_window->show(); };

 private:
  std::unique_ptr<ui::MainWindow> m_window;
  std::shared_ptr<player::Player> m_player;
  std::vector<player::Track> m_tracks;
  void BindWindowEvents();
  void BindPlayerEvents();

};

#endif // KEGERATOR_QT__KEGERATOR_HPP_
