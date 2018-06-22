#ifndef WORMLABEL_H
#define WORMLABEL_H

#include <QString>
#include <QPixmap>
#include <QWidget>
#include "draglabel.h"

class WormLabel: public DragLabel
{
public:
    WormLabel(const QString& image_filename, QWidget* parent, bool original);
    WormLabel(const QPixmap& image, QWidget* parent, bool original);
    bool is_worm();
    ~WormLabel() = default;
};

#endif // WORMLABEL_H
