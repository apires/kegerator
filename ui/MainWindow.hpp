//
// Created by Antonio Jose Pires on 11/13/22.
//

#ifndef KEGERATOR_QT_UI_MAINWINDOW_HPP_
#define KEGERATOR_QT_UI_MAINWINDOW_HPP_

#include "layouts/FlowLayout.hpp"
#include "Player.hpp"
#include "buttons/RoundButton.hpp"
#include <QWidget>
namespace ui {

class MainWindow : public QWidget {
 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

  void AddButton(RoundButton *button);
  void RemoveButton(RoundButton *button);

  void setStopButton();
  void setPlayButton();
  void setSliderMaximum(int max);
  void setSliderPosition(int pos);
  void ShowPlayer();
  void HidePlayer();
  void SetPlayerText(const QString &label);

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
