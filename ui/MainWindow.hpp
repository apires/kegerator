//
// Created by Antonio Jose Pires on 12/12/22.
//

#ifndef KEGERATOR_QT_UI_MAINWINDOW_HPP_
#define KEGERATOR_QT_UI_MAINWINDOW_HPP_

#include <QStackedWidget>
#include <QWidget>
#include "screens/SoundboardScreen.hpp"
#include "screens/ConfigurationScreen.hpp"

namespace ui {
class MainWindow : public QWidget {
 public:
  explicit MainWindow();
  SoundboardScreen *soundboard();
  ConfigurationScreen *configuration();

 private:
  QStackedWidget m_root;
  ConfigurationScreen m_configuration_screen;
  SoundboardScreen m_soundboard_screen;
};
}

#endif //KEGERATOR_QT_UI_MAINWINDOW_HPP_
