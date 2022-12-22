//
// Created by Antonio Jose Pires on 12/12/22.
//

#include <QWidget>
#include <QFileDialog>
#include "MainWindow.hpp"

namespace ui {
MainWindow::MainWindow() : QWidget(nullptr, Qt::WindowType::Window),
                           m_root(this),
                           m_configuration_screen(&m_root),
                           m_soundboard_screen(&m_root),
                           m_toast(this) {
  m_root.setMinimumSize(800, 400);

  m_configuration_screen.InitializeBody();
  m_soundboard_screen.InitializeBody();

  m_root.addWidget(&m_soundboard_screen);
  m_root.addWidget(&m_configuration_screen);

  m_configuration_screen.SetOnMenuButtonClick([this]() {
    m_root.setCurrentWidget(&m_soundboard_screen);
  });
  m_soundboard_screen.SetOnMenuButtonClick([this]() {
    m_root.setCurrentWidget(&m_configuration_screen);
  });

  m_root.show();

}

ConfigurationScreen *MainWindow::configuration() {
  return &m_configuration_screen;
}
SoundboardScreen *MainWindow::soundboard() {
  return &m_soundboard_screen;
}

Toast *MainWindow::toast() {
  return &m_toast;
}

}
