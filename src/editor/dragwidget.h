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
#define ANGLE_DELTA 45

// Widget que representa al escenario, hereda de QWidget. Contiene a los
// widgets que representan a los gusanos y la vigas, manejando la lógica
// necesaria para realizar el drag and drop.

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
