#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QWidget>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMouseEvent>

#define WORM_IMAGE_FILENAME "worm.png"
#define SHORT_BEAM_IMAGE_FILENAME "short_beam.png"
#define LONG_BEAM_IMAGE_FILENAME "long_beam.png"
#define LONG_BEAM_LENGTH 60
#define SHORT_BEAM_LENGTH 30
#define ANGLE_DELTA 45

class DragWidget : public QWidget
{
public:
    explicit DragWidget(QWidget* parent = nullptr);
    ~DragWidget() = default;

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
};

#endif // DRAGWIDGET_H
