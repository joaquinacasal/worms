#include <QString>
#include <QPixmap>
#include <QWidget>
#include <QMatrix>
#include "draglabel.h"
#include "config.h"


DragLabel::DragLabel(const QString& image_filename, QWidget* parent, \
                bool original, int width, int height, int angle, bool is_worm)
    : QLabel(parent), original(original), _width(width), _height(height), \
      angle(angle), _is_worm(is_worm), image_filename(image_filename)
{
    QPixmap image(LABEL_IMAGES_DIR + image_filename);
    image = image.scaled(width * PIXEL_METER_CONVERSION, height * \
                         PIXEL_METER_CONVERSION);
    QMatrix matrix;
    matrix.rotate(-angle);
    image = image.transformed(matrix);
    setPixmap(image);
}

bool DragLabel::is_original() const
{
    return original;
}

bool DragLabel::is_worm() const
{
    return _is_worm;
}

int DragLabel::get_width() const
{
    return _width;
}

int DragLabel::get_height() const
{
    return _height;
}

int DragLabel::get_angle() const
{
    return angle;
}

QString DragLabel::get_image_filename() const
{
    return image_filename;
}
