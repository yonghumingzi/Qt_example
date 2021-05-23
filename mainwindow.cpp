#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->sha1MessagePart->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->sha1FilePart->setTextInteractionFlags(Qt::TextSelectableByMouse);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_messageGenButton_clicked()
{
    if (ui->lineEdit->text() != ""){
        string result = sha_1.generate_SHA1(ui->lineEdit->text().toStdString());
        ui->sha1MessagePart->setText(QString::fromStdString(result));
    }
}

void MainWindow::on_fileImportButton_clicked()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "打开一个文件";
    QString filter = "文本文件(*.txt);;程序文件(*.h *.cpp);;所有文件(*.*)"; //文件过滤器
    QString aFileName = QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if (aFileName.isEmpty())
        return;
    if(openTextByIODevice(aFileName)){
        QStringList tmplist = aFileName.split("/");
        ui->filenameLable->setText(tmplist[tmplist.size()-1]);
    }else{
        ui->filenameLable->setText("Faild to open");
    }
}

bool MainWindow::openTextByIODevice(const QString &aFileName)
{
    QFile aFile(aFileName);
    if (!aFile.exists())
        return false;
    if (!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QByteArray allArray = aFile.readAll();
    QString test = QString(allArray);
    FileContent = test;
    aFile.close();
    return true;
}

void MainWindow::on_fileGenButton_clicked()
{
    if (FileContent != ""){
        string result = sha_1.generate_SHA1(FileContent.toStdString());
        ui->sha1FilePart->setText(QString::fromStdString(result));
    }
}
