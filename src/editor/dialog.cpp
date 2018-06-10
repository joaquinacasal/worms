#include <QDialog>
#include <QWidget>
#include "dialog.h"
#include "mainwindow.h"
#include "ui_dialog.h"

class MainWindow;

Dialog::Dialog(MainWindow* window, int width, int heigth) :
    main_window(window), QDialog(window), scenario_width(width), scenario_heigth(heigth),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->errorLabel->hide();
    ui->widthInput->appendPlainText(QString::number(scenario_width));
    ui->heigthInput->appendPlainText(QString::number(scenario_heigth));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_updateButton_clicked()
{
    int heigth_input = ui->heigthInput->toPlainText().toInt();
    int width_input = ui->widthInput->toPlainText().toInt();
    if (heigth_input == 0 || width_input == 0){
        ui->errorLabel->show();
    } else {
        scenario_heigth = heigth_input;
        scenario_width = width_input;
        main_window->set_widget_size(scenario_width, scenario_heigth);
        ui->errorLabel->hide();
    }
}

void Dialog::on_QuitButton_clicked()
{
    accept();
}
