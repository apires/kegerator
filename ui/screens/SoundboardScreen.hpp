//
// Created by Antonio Jose Pires on 12/8/22.
//

#ifndef KEGERATOR_QT_UI_SCREENS_SOUNDBOARDSCREEN_HPP_
#define KEGERATOR_QT_UI_SCREENS_SOUNDBOARDSCREEN_HPP_

#include "KegeratorScreen.hpp"
#include "../buttons/RoundButton.hpp"
#include "../layouts/FlowLayout.hpp"
#include "../Player.hpp"
namespace ui {
class SoundboardScreen : public KegeratorScreen {

 public:
  void InitializeBody() override;

  void AddButton(RoundButton *button) { body().layout()->addWidget(button); }
  void RemoveButton(RoundButton *button) { body().layout()->removeWidget(button); }

  void SetStopButton() { m_player.setStopButton(); }
  void SetPlayButton() { m_player.setPlayButton(); }
  void SetSliderMaximum(int max) { m_player.setSliderMaximum(max); }
  void SetSliderPosition(int pos) { m_player.setSliderPosition(pos); }
  void ShowPlayer() { m_player.show(); }
  void HidePlayer() { m_player.hide(); }
  void SetPlayerText(const QString &label) { m_player.setPlayerText(label); }

  std::function<void()> onPlayButtonClick;

 private:
  QWidget m_button_grid;
  Player m_player;

};
}

#endif //KEGERATOR_QT_UI_SCREENS_SOUNDBOARDSCREEN_HPP_
