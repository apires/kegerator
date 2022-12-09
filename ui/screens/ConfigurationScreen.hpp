//
// Created by Antonio Jose Pires on 12/8/22.
//

#ifndef KEGERATOR_QT_UI_CONFIGURATIONWINDOW_HPP_
#define KEGERATOR_QT_UI_CONFIGURATIONWINDOW_HPP_

#include <QWidget>
#include "../layouts/FlowLayout.hpp"

namespace ui {

class ConfigurationScreen : public QWidget {
 public:
  explicit ConfigurationScreen(QWidget *parent = nullptr);
  void AddOption(const QString &label, const std::function<void(void)> &onClick);

 private:
  QVBoxLayout m_root_layout;
  QWidget m_button_grid;
  FlowLayout m_button_grid_layout;

};
} // ui

#endif //KEGERATOR_QT_UI_CONFIGURATIONWINDOW_HPP_
