#ifndef COMTHREAD_H
#define COMTHREAD_H

#include <QThread>
#include <QObject>
#include <QDebug>

#include <Windows.h>
#include <iostream>

class ComThread : public QThread
{
    Q_OBJECT

private:
    QString name;
    HANDLE hSerial;
    float temp;
    float humidity;

public:
    ComThread(QString n);
    QString getName() { return name; }
    float getTemp() { return temp; };
    float getHumidity() { return humidity; }
    void setup();
    void run();

protected:

signals:
    void sendData(QString data);
    void sendData(QString name, QString data);
    void sendError(QString name, QString error);
};

#endif // COMTHREAD_H
