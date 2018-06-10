#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include <QString>
#include <QLabel>
#include <QPixmap>
#include <QWidget>

class DragLabel : public QLabel
{
private:
    bool original;
    int length;
    int angle;
    bool _is_worm;
    QString image_filename;

public:
    DragLabel(const QString& image_filename, QWidget* parent, bool original, int length, int angle, bool is_worm);
    bool is_original() const;
    bool is_worm() const;
    int get_length() const;
    int get_angle() const;
    QString get_image_filename() const;
};

#endif // DRAGLABEL_H
