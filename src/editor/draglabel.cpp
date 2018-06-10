#include <QString>
#include <QPixmap>
#include <QWidget>
#include "draglabel.h"
#include "config.h"


DragLabel::DragLabel(const QString& image_filename, QWidget* parent, bool original, int length, int angle, bool is_worm)
    : QLabel(parent), original(original), length(length), angle(angle), _is_worm(is_worm), image_filename(image_filename)
{
    QPixmap image(LABEL_IMAGES_DIR + image_filename);
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

int DragLabel::get_length() const
{
    return length;
}

int DragLabel::get_angle() const
{
    return angle;
}

QString DragLabel::get_image_filename() const
{
    return image_filename;
}
