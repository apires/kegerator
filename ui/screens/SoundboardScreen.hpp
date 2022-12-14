//
// Created by Antonio Jose Pires on 12/8/22.
//

#ifndef KEGERATOR_QT_UI_SCREENS_SOUNDBOARDSCREEN_HPP_
#define KEGERATOR_QT_UI_SCREENS_SOUNDBOARDSCREEN_HPP_

#include "KegeratorScreen.hpp"
#include "../buttons/RoundButton.hpp"
#include "../layouts/FlowLayout.hpp"
#include "../Player.hpp"
#include "glog/logging.h"

namespace ui {
class SoundboardScreen : public KegeratorScreen {

 public:
  explicit SoundboardScreen(QWidget *p_widget) : KegeratorScreen(p_widget), m_player(this) {
    SetMenuIcon(MenuIcon::Grid);
  }
  void InitializeBody() override;
  void AddButton(RoundButton *button);
  void RemoveButton(RoundButton *button);
  std::function<void()> onPlayButtonClick;

  ui::Player &Player() { return m_player; }
  void SetPlayerText(const QString &label) { m_player.setPlayerText(label); }

 private:
  QWidget m_button_grid;
  ui::Player m_player;
};
}

#endif //KEGERATOR_QT_UI_SCREENS_SOUNDBOARDSCREEN_HPP_
