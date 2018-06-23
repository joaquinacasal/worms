#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Dialog;
}

class MainWindow;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(MainWindow* window, int width, int height);
    ~Dialog();

private slots:

    void on_updateButton_clicked();

    void on_QuitButton_clicked();

private:
    Ui::Dialog *ui;
    MainWindow* main_window;
    int scenario_width;
    int scenario_height;
};

#endif // DIALOG_H
