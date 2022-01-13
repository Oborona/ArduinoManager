#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{

    ComThread* thread = new ComThread("COM6");
//    connect(thread, SIGNAL(sendData(QString,QString)), this, SLOT(getData(QString,QString)));

    DataIndicator* di = new DataIndicator(this);
    di->setTitle("Комната");
    indicators.push_back(di);
    di->connectWithThread(thread);

    layout = new QGridLayout();
    layout->addWidget(indicators[0], 0, 0);
    thread->setup();
    thread->start();
}

void MainWindow::getData(QString name, QString data)
{

}
