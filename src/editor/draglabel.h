#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include <QString>
#include <QLabel>
#include <QPixmap>
#include <QWidget>

// Label que representa a un gusano o una viga, hereda de QLabel. Son los
// objetos que el usuario arrastra por la pantalla para diseñar el nivel.
// Contienen una imagen para identificarlos.
class DragLabel : public QLabel
{
private:
    bool original;
    int _width;
    int _height;
    int angle;
    bool _is_worm;
    QString image_filename;

public:
    DragLabel(const QString& image_filename, QWidget* parent, bool original,\
              int width, int height, int angle, bool is_worm);
    bool is_original() const;
    bool is_worm() const;
    int get_width() const;
    int get_height() const;
    int get_angle() const;
    QString get_image_filename() const;
    ~DragLabel() = default;
};

#endif // DRAGLABEL_H
