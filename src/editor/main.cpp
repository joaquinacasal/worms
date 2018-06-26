#include <iostream>
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) try
{
    QApplication app(argc, argv);
    MainWindow window;
    window.showMaximized();
    window.show_dialog();
    return app.exec();
} catch (...){
  std::cout << "Ocurrió un problema" << std::endl;
  return -1;
}
