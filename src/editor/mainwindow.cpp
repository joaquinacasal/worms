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
    int screen_width = pixels_to_meters(screen->geometry().width());
    int screen_heigth = pixels_to_meters(screen->geometry().height());
    set_widget_size(screen_width, screen_heigth);
    input_dialog = new Dialog(this, screen_width, screen_heigth);
    input_dialog->setAttribute(Qt::WA_DeleteOnClose);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show_dialog(){
    input_dialog->show();
}

void MainWindow::set_widget_size(int width, int heigth)
{
    scenario["width"] = std::to_string(width);
    scenario["heigth"] = std::to_string(heigth);
    scenario_widget->resize(meters_to_pixels(width), meters_to_pixels(heigth));
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
        if (!label->is_original() && label->is_worm()){
            worms_labels.append(label);
        }
    }
    return worms_labels;
}

QList<DragLabel*> MainWindow::get_beams(){
    QList<DragLabel*> labels = scenario_widget->findChildren<DragLabel*>();
    QList<DragLabel*> beams_labels;
    for (DragLabel* label : labels){
        if (!label->is_original() && !label->is_worm()){
            beams_labels.append(label);
        }
    }
    return beams_labels;
}

bool MainWindow::check_intersections(){
    QList<DragLabel*> labels = scenario_widget->findChildren<DragLabel*>();
    for (DragLabel* label : labels){
        for (DragLabel* other_label : labels){
            if (label == other_label){
                continue;
            }
            if (label->geometry().intersects(other_label->geometry())){
                return true;
            }
        }
    }
    return false;
}

int MainWindow::pixels_to_meters(int pixels)
{
    return pixels / PIXEL_METER_CONVERSION;
}

int MainWindow::meters_to_pixels(int meters)
{
    return meters * PIXEL_METER_CONVERSION;
}

void MainWindow::on_actionLoad_background_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, SELECT_BACKGROUND_MESSAGE, BACKGROUND_IMAGES_DIR);
    if (filename == "")
        return;
    filename = filename.split('/').last();
    scenario["background"] = filename.toStdString();
    load_background(filename);
}

void MainWindow::on_actionOpen_scenario_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, SELECT_SCENARIO_MESSAGE, SCENARIO_FILES_DIR);
    if (filename == "")
        return;
    current_file = filename;
    QList<DragLabel*> old_labels = scenario_widget->findChildren<DragLabel*>();
    for (DragLabel* old_label : old_labels){
        if (!old_label->is_original()){
            old_label->clear();
            old_label->close();
        }
    }
    YAML::Node new_scenario = YAML::LoadFile(filename.toStdString());

    scenario = new_scenario["scenario"].as<map<string, string>>();
    int heigth = std::stoi(scenario.at("heigth"));
    int width = std::stoi(scenario.at("width"));
    string background = scenario.at("background");
    set_widget_size(width, heigth);
    load_background(QString::fromStdString(background));

    vector<map<string, string>> worms = new_scenario["worms"].as<vector<map<string, string>>>();
    vector<map<string, string>> beams = new_scenario["beams"].as<vector<map<string, string>>>();

    for (map<string, string> worm : worms){
        int x = meters_to_pixels(std::stoi(worm.at("x")));
        int y = std::stoi(worm.at("y"));
        y = meters_to_pixels((y - heigth) * -1);
        QString image_filename = QString::fromStdString(worm.at("image"));
        DragLabel* new_worm = new DragLabel(image_filename, scenario_widget, false, 2, 0, true);
        //x -= new_worm->rect().center().x();
        //y -= new_worm->rect().center().y();
        new_worm->move(x, y);
        new_worm->show();
        new_worm->setAttribute(Qt::WA_DeleteOnClose);
    }

    for (map<string, string> beam : beams){
        int x = meters_to_pixels(std::stoi(beam.at("x")));
        int y = std::stoi(beam.at("y"));
        y = meters_to_pixels((y - heigth) * -1);
        int length = std::stoi(beam.at("length"));
        int angle = std::stoi(beam.at("angle"));
        QString image_filename = QString::fromStdString(beam.at("image"));
        DragLabel* new_beam = new DragLabel(image_filename, scenario_widget, false, length, angle, false);
        //x -= new_beam->rect().center().x();
        //y -= new_beam->rect().center().y();
        new_beam->move(x, y);
        new_beam->show();
        new_beam->setAttribute(Qt::WA_DeleteOnClose);
    }
}

void MainWindow::on_actionSave_scenario_triggered()
{
    if (check_intersections()){
        QMessageBox message(this);
        message.setText(OVERLAPPING_MESSAGE);
        message.exec();
        return;
    }

    QList<DragLabel*> worms_labels = get_worms();
    QList<DragLabel*> beams_labels = get_beams();

    if (worms_labels.empty()){
        QMessageBox message(this);
        message.setText(NO_WORMS_MESSAGE);
        message.exec();
        return;
    }

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

    YAML::Emitter parser;
    parser << YAML::BeginMap;
    parser << YAML::Key << "scenario";
    parser << YAML::Value << scenario;

    parser << YAML::Key << "worms";
    parser << YAML::Value << YAML::BeginSeq;
    int id_counter = 1;
    int scenario_heigth = std::stoi(scenario.at("heigth"));
    for (DragLabel* worm_label : worms_labels){
        int x = pixels_to_meters(worm_label->pos().x());
        int y = pixels_to_meters(worm_label->pos().y());
        y = y * -1 + scenario_heigth;
        //x += worm_label->rect().center().x();
        //y += worm_label->rect().center().y();
        std::map<string, string> worm;
        worm["id"] = std::to_string(id_counter);
        worm["x"] = std::to_string(x);
        worm["y"] = std::to_string(y);
        worm["image"] = worm_label->get_image_filename().toStdString();
        parser << worm;
    }
    parser << YAML::EndSeq;

    parser << YAML::Key << "beams";
    parser << YAML::Value << YAML::BeginSeq;
    id_counter = 1;
    for (DragLabel* beam_label : beams_labels){
        int x = pixels_to_meters(beam_label->pos().x());
        int y = pixels_to_meters(beam_label->pos().y());
        y = y * -1 + scenario_heigth;
        //x += beam_label->rect().center().x();
        //y += beam_label->rect().center().y();
        std::map<string, string> beam;
        beam["id"] = std::to_string(id_counter);
        beam["x"] = std::to_string(x);
        beam["y"] = std::to_string(y);
        beam["length"] = std::to_string(beam_label->get_length());
        beam["angle"] = std::to_string(beam_label->get_angle());
        beam["image"] = beam_label->get_image_filename().toStdString();
        parser << beam;
    }
    parser << YAML::EndSeq << YAML::EndMap;

    std::ofstream fout(filename.toStdString());
    fout << parser.c_str();
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
    QDialog* input_dialog = new Dialog(this, std::stoi(scenario["width"]), std::stoi(scenario["heigth"]));
    input_dialog->setAttribute(Qt::WA_DeleteOnClose);
    input_dialog->show();
}
