#include "draglabel.h"
#include "wormlabel.h"
#include "beamlabel.h"
#include "dragwidget.h"
#include <QtWidgets>
#include <string>
#include <vector>

static inline QString wormsLabelMimeType() { return QStringLiteral("application/x-wormlabel"); }

DragWidget::DragWidget(QWidget *parent)
    : QWidget(parent)
{
    int x = 5;
    int y = 5;

    DragLabel* worm = new DragLabel(WORM_IMAGE_FILENAME, this, true, 2, 0, true);
    worm->move(x, y);
    worm->show();
    worm->setAttribute(Qt::WA_DeleteOnClose);
    y += worm->height() + 2;

    for (int n = 0 ; n < 2 ; n++){
        for (int i = 0 ; i < 4 ; i++){
            QString beam_image_filename;
            int beam_length;
            QString i_str = QString::fromStdString(std::to_string(i));
            if (n == 0){
                beam_image_filename = LONG_BEAM_PREFIX + i_str + IMAGE_EXTENSION;
                beam_length = LONG_BEAM_LENGTH;
            } else {
                beam_image_filename = SHORT_BEAM_PREFIX + i_str + IMAGE_EXTENSION;
                beam_length = SHORT_BEAM_LENGTH;
            }
            float current_angle = ANGLE_DELTA * i;
            DragLabel* beam = new DragLabel(beam_image_filename, this, true, beam_length, current_angle, false);
            beam->move(x, y);
            beam->show();
            beam->setAttribute(Qt::WA_DeleteOnClose);
            y += beam->height() + 2;
        }
    }

    setAcceptDrops(true);
    QPalette palette;
    palette.setColor(QPalette::Background, Qt::black);
    setPalette(palette);
}

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->setDropAction(Qt::MoveAction);
    event->accept();
}

void DragWidget::dragMoveEvent(QDragMoveEvent *event)
{
    event->setDropAction(Qt::MoveAction);
    event->accept();
}

void DragWidget::dropEvent(QDropEvent *event)
{
    const QMimeData* mime = event->mimeData();
    QByteArray itemData = mime->data(wormsLabelMimeType());
    QDataStream dataStream(&itemData, QIODevice::ReadOnly);
    QString image_filename;
    QPoint offset;
    int length;
    int angle;
    bool is_worm;
    dataStream >> image_filename >> offset >> length >> angle >> is_worm;
    DragLabel* newLabel = new DragLabel(image_filename, this, false, length, angle, is_worm);
    newLabel->move(event->pos() - offset);
    newLabel->show();
    newLabel->setAttribute(Qt::WA_DeleteOnClose);
    event->setDropAction(Qt::MoveAction);
    event->accept();
}

void DragWidget::mousePressEvent(QMouseEvent *event)
{
    DragLabel* child = static_cast<DragLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QPoint hotSpot = event->pos() - child->pos();
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << child->get_image_filename() << QPoint(hotSpot) << child->get_length() << child->get_angle() << child->is_worm();
    QMimeData* mimeData = new QMimeData;
    mimeData->setData(wormsLabelMimeType(), itemData);
    QDrag* drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(*child->pixmap());
    drag->setHotSpot(hotSpot);
    bool original = child->is_original();
    if (!original){
        child->hide();
    }
    drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction);
    if (original){
        child->show();
    } else {
        child->close();
    }
}
