//
// Created by Antonio Jose Pires on 12/25/22.
//

#ifndef KEGERATOR_QT_UI_COLOR_COLORPICKER_HPP_
#define KEGERATOR_QT_UI_COLOR_COLORPICKER_HPP_

#include <QFile>
#include <QColor>

namespace ui::ColorPicker {
QColor forPath(const std::filesystem::path &path);
}

#endif //KEGERATOR_QT_UI_COLOR_COLORPICKER_HPP_
