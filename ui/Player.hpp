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
#include <QLabel>

namespace ui {
class Player : public QWidget {

 public:
  explicit Player(QWidget *parent = nullptr);
  void setPlayButton();
  void setStopButton();
  void setSliderMaximum(int max);
  void setSliderPosition(int pos);
  void setPlayerText(const QString &label);

  std::function<void()> onPlayButtonClick;

 private:
  const QString STOP_ICON = "⏹";
  const QString PLAY_ICON = "⏵";

  QVBoxLayout m_layout;

  // Metadata Section
  QWidget m_metadata{this};
  QHBoxLayout m_metadata_layout;
  QLabel m_metadata_label;

  // AudioPlayer Control
  QWidget m_player_control{this};
  QHBoxLayout m_player_control_layout;
  QSlider m_slider;
  QPushButton m_button;
  void InitializePlayerControls();
  void InitializeMetadataSection();

 protected:
  void showEvent(QShowEvent *event) override;

};
}
#endif // KEGERATOR_QT_UI_PLAYER_HPP_
