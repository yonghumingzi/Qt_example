#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include "sha-1.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_messageGenButton_clicked();

    void on_fileImportButton_clicked();

    void on_fileGenButton_clicked();

    bool openTextByIODevice(const QString &aFileName);

private:
    Ui::MainWindow *ui;
    SHA_1 sha_1;
    QString FileContent;
};

#endif // MAINWINDOW_H
