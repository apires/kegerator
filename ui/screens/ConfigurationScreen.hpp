//
// Created by Antonio Jose Pires on 12/8/22.
//

#ifndef KEGERATOR_QT_UI_CONFIGURATIONWINDOW_HPP_
#define KEGERATOR_QT_UI_CONFIGURATIONWINDOW_HPP_

#include <QWidget>
#include "../layouts/FlowLayout.hpp"
#include "KegeratorScreen.hpp"

namespace ui {

class ConfigurationScreen : public KegeratorScreen {
 public:
  explicit ConfigurationScreen(QWidget *p_widget) : KegeratorScreen(p_widget) {
    SetMenuIcon(MenuIcon::X);
  }
  void AddOption(const QString &label, const std::function<void(void)> &onClick);
  void AddOption(QIcon icon, const std::function<void(void)> &onClick);
  void InitializeBody() override;
};
} // ui

#endif //KEGERATOR_QT_UI_CONFIGURATIONWINDOW_HPP_
