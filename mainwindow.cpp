#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    ComThread* thread = new ComThread("COM6");
    connect(thread, SIGNAL(sendData(QString,QString)), this, SLOT(getData(QString,QString)));
    thread->setup();
    thread->start();
}

void MainWindow::getData(QString name, QString data)
{
    qDebug() << name << data;
}
