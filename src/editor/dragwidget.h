#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QWidget>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMouseEvent>

#define LONG_BEAM_PREFIX "grdl"
#define SHORT_BEAM_PREFIX "grds"
#define WORM_IMAGE_FILENAME "worm.png"
#define IMAGE_EXTENSION ".png"
#define LONG_BEAM_LENGTH 8
#define SHORT_BEAM_LENGTH 4
#define ANGLE_DELTA 45

class DragWidget : public QWidget
{
public:
    explicit DragWidget(QWidget* parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
};

#endif // DRAGWIDGET_H
