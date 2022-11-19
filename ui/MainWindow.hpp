//
// Created by Antonio Jose Pires on 11/13/22.
//

#ifndef KEGERATOR_QT_UI_MAINWINDOW_HPP_
#define KEGERATOR_QT_UI_MAINWINDOW_HPP_

#include "../lib/FlowLayout.hpp"
#include "Player.hpp"
#include "RoundButton.hpp"
#include <QWidget>
namespace ui {

class MainWindow : public QWidget {
 public:
  explicit MainWindow(QWidget *parent = nullptr);

  void AddButton(RoundButton *button) {
    m_button_grid_layout.addWidget(button);
  }
  void RemoveButton(RoundButton *button) {
    m_button_grid_layout.removeWidget(button);
  }

  void setStopButton() { m_player.setStopButton(); }
  void setPlayButton() { m_player.setPlayButton(); }
  void setSliderMaximum(int max) { m_player.setSliderMaximum(max); }
  void setSliderPosition(int pos) { m_player.setSliderPosition(pos); }
  void ShowPlayer() { m_player.show(); }
  void HidePlayer() { m_player.hide(); }
  void SetPlayerText(const QString &label) { m_player.setPlayerText(label); }

  std::function<void()> onPlayButtonClick;

 private:
  QVBoxLayout m_root_layout;
  QWidget m_button_grid;
  FlowLayout m_button_grid_layout;
  QPushButton m_kebab_menu;
  Player m_player;

  void InitializeKebabMenu();
};
} // namespace ui

#endif // KEGERATOR_QT_UI_MAINWINDOW_HPP_
