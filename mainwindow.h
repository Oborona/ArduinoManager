#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QGridLayout>

#include "comthread.h"
#include "dataindicator.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    QGridLayout* layout;
    QList<DataIndicator*> indicators;

public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:


public slots:
    void getData(QString name, QString data);

};

#endif // MAINWINDOW_H
