//
// Created by Antonio Jose Pires on 11/13/22.
//

#ifndef KEGERATOR_QT_UI_PLAYER_HPP_
#define KEGERATOR_QT_UI_PLAYER_HPP_

#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QWidget>
#include <QObject>

class Player : public QWidget {

 public:
  explicit Player(QWidget *parent = nullptr);
  void setPlayButton();
  void setStopButton();
  void setSliderMaximum(int max);
  void setSliderPosition(int pos);

  std::function<void()> onPlayButtonClick;

 private:
  const QString STOP_ICON = "⏹";
  const QString PLAY_ICON = "⏵";

  QHBoxLayout m_layout;
  QSlider m_slider;
  QPushButton m_button;
};

#endif // KEGERATOR_QT_UI_PLAYER_HPP_
