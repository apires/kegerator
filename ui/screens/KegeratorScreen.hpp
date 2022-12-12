//
// Created by Antonio Jose Pires on 12/8/22.
//

#ifndef KEGERATOR_QT_UI_SCREENS_KEGERATORSCREEN_HPP_
#define KEGERATOR_QT_UI_SCREENS_KEGERATORSCREEN_HPP_

#include <QVBoxLayout>
#include <QPushButton>

namespace ui {
class KegeratorScreen : public QWidget {
 public:
  enum MenuIcon {
    Hamburger,
    X
  };

  explicit KegeratorScreen(QWidget *parent = nullptr);
  void SetMenuIcon(MenuIcon icon);
  virtual void InitializeBody();

 private:
  QWidget m_header;
  QWidget m_body;
  QPushButton m_menu_button;
  std::function<void()> onMenuButtonClick;

 public:
  void SetOnMenuButtonClick(const std::function<void()> &);
 private:

  void InitializeHeader();

  static QString getMenuIconRepresentation(MenuIcon icon);

 protected:
  QWidget &body();

};
}
#endif //KEGERATOR_QT_UI_SCREENS_KEGERATORSCREEN_HPP_
