#ifndef BEAMLABEL_H
#define BEAMLABEL_H

#include <QString>
#include <QPixmap>
#include <QWidget>
#include "draglabel.h"

class BeamLabel: public DragLabel
{
private:
    int length;
    int angle;

public:
    BeamLabel(const QString& image_filename, QWidget* parent, bool original, int length, int angle);
    BeamLabel(const QPixmap& image, QWidget* parent, bool original, int length, int angle);
    bool is_worm();
};

#endif // BEAMLABEL_H
