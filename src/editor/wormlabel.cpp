#include "wormlabel.h"
#include "draglabel.h"
#include <QString>
#include <QPixmap>
#include <QWidget>

WormLabel::WormLabel(const QString &image_filename, QWidget *parent, \
                     bool original)
     {}

WormLabel::WormLabel(const QPixmap &image, QWidget *parent, bool original)
    {}

bool WormLabel::is_worm()
{
    return true;
}
