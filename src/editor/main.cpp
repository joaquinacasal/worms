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
} catch (std::exception& ex){
    std::cout << ex.what() << std::endl;
    return -1;
} catch (...){
  std::cout << "Ocurrió un problema" << std::endl;
  return -1;
}
