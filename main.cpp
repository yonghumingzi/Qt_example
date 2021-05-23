#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("SHA-1 Digest Generation");
    w.show();
    return a.exec();
}
