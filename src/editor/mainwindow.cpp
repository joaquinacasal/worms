#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QPalette>
#include <QPixmap>
#include <QScreen>
#include <QScrollArea>
#include <QList>
#include "yaml-cpp/yaml.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dragwidget.h"
#include "draglabel.h"
#include "dialog.h"
#include "config.h"

using std::string;
using std::vector;
using std::map;

class Dialog;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QScrollArea* scroll_area = new QScrollArea();
    scroll_area->setAttribute(Qt::WA_DeleteOnClose);
    scenario_widget = new DragWidget();
    scenario_widget->setAttribute(Qt::WA_DeleteOnClose);
    scroll_area->setWidget(scenario_widget);
    setCentralWidget(scroll_area);
    setWindowTitle(tr("Worms"));
    setWindowIcon(QIcon(QString(LABEL_IMAGES_DIR) + QString(WORM_IMAGE_FILENAME)));

    QScreen* screen = QGuiApplication::primaryScreen();
    int screen_width = scenario.pixels_to_meters(screen->geometry().width());
    int screen_height = scenario.pixels_to_meters(screen->geometry().height());
    set_widget_size(screen_width, screen_height);
    input_dialog = new Dialog(this, screen_width, screen_height);
    input_dialog->setAttribute(Qt::WA_DeleteOnClose);
}

MainWindow::~MainWindow()
{
    delete_labels(true);
    delete ui;
}

void MainWindow::show_dialog(){
    input_dialog->show();
}

void MainWindow::set_widget_size(int width, int height)
{
    scenario.set_size(width, height);
    scenario_widget->resize(scenario.meters_to_pixels(width), scenario.meters_to_pixels(height));
}

void MainWindow::load_background(QString filename){
    QPixmap background(BACKGROUND_IMAGES_DIR + filename);
    background = background.scaled(scenario_widget->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    scenario_widget->setPalette(palette);
}

QList<DragLabel*> MainWindow::get_worms(){
    QList<DragLabel*> labels = scenario_widget->findChildren<DragLabel*>();
    QList<DragLabel*> worms_labels;
    for (DragLabel* label : labels){
        if (label->is_worm() && !label->is_original()){
            worms_labels.append(label);
        }
    }
    return worms_labels;
}

QList<DragLabel*> MainWindow::get_beams(){
    QList<DragLabel*> labels = scenario_widget->findChildren<DragLabel*>();
    QList<DragLabel*> beams_labels;
    for (DragLabel* label : labels){
        if (!label->is_worm() && !label->is_original()){
            beams_labels.append(label);
        }
    }
    return beams_labels;
}

void MainWindow::delete_labels(bool include_originals){
    QList<DragLabel*> labels = scenario_widget->findChildren<DragLabel*>();
    if (include_originals){
        for (DragLabel* label : labels){
            label->clear();
            label->close();
        }
    } else {
        for (DragLabel* label : labels){
            if (!label->is_original()){
                label->clear();
                label->close();
            }
        }
    }
}

void MainWindow::on_actionLoad_background_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, SELECT_BACKGROUND_MESSAGE, BACKGROUND_IMAGES_DIR);
    if (filename == "")
        return;
    filename = filename.split('/').last();
    scenario.set_background(filename.toStdString());
    load_background(filename);
}

void MainWindow::on_actionOpen_scenario_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, SELECT_SCENARIO_MESSAGE, SCENARIO_FILES_DIR);
    if (filename == "")
        return;
    current_file = filename;
    delete_labels(false);

    int height;
    int width;
    string background;
    vector<map<string, string>> worms;
    vector<map<string, string>> beams;
    scenario.load_scenario(filename.toStdString(), height, width, background, worms, beams);

    set_widget_size(width, height);
    load_background(QString::fromStdString(background));
    for (map<string, string> worm : worms){
        float x = std::stof(worm.at("x"));
        float y = std::stof(worm.at("y"));
        QString image_filename = QString::fromStdString(worm.at("image"));
        DragLabel* new_worm = new DragLabel(image_filename, scenario_widget, false, WORM_SIZE, WORM_SIZE, 0, true);
        new_worm->move(x, y);
        new_worm->show();
        new_worm->setAttribute(Qt::WA_DeleteOnClose);
    }
    for (map<string, string> beam : beams){
        float x = std::stof(beam.at("x"));
        float y = std::stof(beam.at("y"));
        int length = std::stoi(beam.at("length"));
        int height = std::stoi(beam.at("height"));
        int angle = std::stoi(beam.at("angle"));
        QString image_filename = QString::fromStdString(beam.at("image"));
        DragLabel* new_beam = new DragLabel(image_filename, scenario_widget, false, length, height, angle, false);
        new_beam->move(x, y);
        new_beam->show();
        new_beam->setAttribute(Qt::WA_DeleteOnClose);
    }
}

void MainWindow::on_actionSave_scenario_triggered()
{
    QString filename;
    if (current_file.isEmpty()) {
        filename = QFileDialog::getSaveFileName(this, SAVE_SCENARIO_MESSAGE, SCENARIO_FILES_DIR);
        if (filename == ""){
            return;
        }
        current_file = filename;
    } else {
        filename = current_file;
    }
    
    QList<DragLabel*> worms_labels = get_worms();
    QList<DragLabel*> beams_labels = get_beams();
    int status = scenario.save_scenario(worms_labels, beams_labels, filename.toStdString());
    if (status == 1){
        QMessageBox message(this);
        message.setText(OVERLAPPING_MESSAGE);
        message.exec();
        return;
    } else if (status == 2){
        QMessageBox message(this);
        message.setText(NO_WORMS_MESSAGE);
        message.exec();
        return;
    }
    QMessageBox message(this);
    message.setText(SAVE_SCENARIO_SUCCESS);
    message.exec();
}

void MainWindow::on_actionSave_scenario_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, SAVE_SCENARIO_MESSAGE, SCENARIO_FILES_DIR);
    if (filename == ""){
        return;
    }
    current_file = filename;
    on_actionSave_scenario_triggered();
}

void MainWindow::on_actionChange_size_triggered()
{
    QDialog* input_dialog = new Dialog(this, scenario.get_width(), scenario.get_height());
    input_dialog->setAttribute(Qt::WA_DeleteOnClose);
    input_dialog->show();
}
