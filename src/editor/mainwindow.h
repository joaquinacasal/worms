#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <map>
#include <QWidget>
#include <QMainWindow>
#include <QList>
#include "dialog.h"
#include "draglabel.h"
#include "scenariosaver.h"

#define PIXEL_METER_CONVERSION 10
#define SAVE_SCENARIO_MESSAGE "Guardar escenario"
#define NO_WORMS_MESSAGE "Tenés que agregar algún gusano para guardar el escenario"
#define OVERLAPPING_MESSAGE "Hay elementos que se solapan. Separalos para guardar el escenario"
#define SELECT_SCENARIO_MESSAGE "Seleccioná un escenario"
#define SELECT_BACKGROUND_MESSAGE "Seleccioná una imagen de fondo"
#define SAVE_SCENARIO_SUCCESS "Se guardó correctamente el escenario"

namespace Ui {
class MainWindow;
}

class Dialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow* ui;
    QWidget* scenario_widget;
    Dialog* input_dialog;
    ScenarioSaver scenario;
    QString current_file;

    void load_background(QString filename);
    QList<DragLabel*> get_worms();
    QList<DragLabel*> get_beams();
    void delete_labels(bool include_originals);

public:
    explicit MainWindow(QWidget* parent = 0);
    void show_dialog();
    void set_widget_size(int width, int height);
    ~MainWindow();

private slots:
    void on_actionLoad_background_triggered();
    void on_actionOpen_scenario_triggered();
    void on_actionSave_scenario_triggered();
    void on_actionSave_scenario_as_triggered();
    void on_actionChange_size_triggered();
};

#endif // MAINWINDOW_H
