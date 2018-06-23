#include <QDialog>
#include <QWidget>
#include "dialog.h"
#include "mainwindow.h"
#include "ui_dialog.h"

class MainWindow;

Dialog::Dialog(MainWindow* window, int width, int height) :
    main_window(window), QDialog(window), scenario_width(width), scenario_height(height),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->errorLabel->hide();
    ui->widthInput->appendPlainText(QString::number(scenario_width));
    ui->heightInput->appendPlainText(QString::number(scenario_height));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_updateButton_clicked()
{
    int height_input = ui->heightInput->toPlainText().toInt();
    int width_input = ui->widthInput->toPlainText().toInt();
    if (height_input == 0 || width_input == 0){
        ui->errorLabel->show();
    } else {
        scenario_height = height_input;
        scenario_width = width_input;
        main_window->set_widget_size(scenario_width, scenario_height);
        ui->errorLabel->hide();
    }
}

void Dialog::on_QuitButton_clicked()
{
    accept();
}
