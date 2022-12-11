//
// Created by Antonio Jose Pires on 11/13/22.
//

#include <QLabel>
#include "MainWindow.hpp"

namespace ui {
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent, Qt::WindowFlags::enum_type::Widget) {
  setMinimumSize(800, 600);
  setStyleSheet("background-color: #51B3F0;");
  setLayout(&m_root_layout);

  InitializeKebabMenu();

  m_button_grid.setLayout(&m_button_grid_layout);

  m_root_layout.addWidget(&m_kebab_menu, 0,
                          Qt::Alignment::enum_type::AlignRight);
  m_root_layout.addWidget(&m_button_grid, 1);
  m_root_layout.addWidget(&m_player, 0, Qt::Alignment::enum_type::AlignCenter);

  m_player.setFixedWidth(width() / 2);
  m_player.onPlayButtonClick = [this]() {
    if (onPlayButtonClick) onPlayButtonClick();
  };
  m_player.hide();
}

void MainWindow::InitializeKebabMenu() {
  m_kebab_menu.setFixedSize(40, 40);
  m_kebab_menu.setStyleSheet(
      "QPushButton, QLabel { background: white; border: none; font-size: 24px; border-radius: 4px;} ");

  auto lbl = new QLabel(&m_kebab_menu);
  lbl->setText("☰");
  lbl->setFixedWidth(40);
  lbl->setFixedHeight(38);
  lbl->setAlignment(Qt::Alignment::enum_type::AlignCenter);

}
void MainWindow::setPlayButton() { m_player.setPlayButton(); }
void MainWindow::setStopButton() { m_player.setStopButton(); }
void MainWindow::RemoveButton(RoundButton *button) { m_button_grid_layout.removeWidget(button); }
void MainWindow::AddButton(RoundButton *button) { m_button_grid_layout.addWidget(button); }
void MainWindow::setSliderMaximum(int max) { m_player.setSliderMaximum(max); }
void MainWindow::setSliderPosition(int pos) { m_player.setSliderPosition(pos); }
void MainWindow::ShowPlayer() { m_player.show(); }
void MainWindow::HidePlayer() { m_player.hide(); }
void MainWindow::SetPlayerText(const QString &label) { m_player.setPlayerText(label); }
MainWindow::~MainWindow() {}
} // namespace ui
