#include "beamlabel.h"
#include "draglabel.h"
#include <QString>
#include <QPixmap>
#include <QWidget>

BeamLabel::BeamLabel(const QString &image_filename, QWidget *parent,\
                     bool original, int length, int angle)
    {}

BeamLabel::BeamLabel(const QPixmap &image, QWidget *parent, bool original,\
                     int length, int angle)
     {}

bool BeamLabel::is_worm()
{
    return false;
}
