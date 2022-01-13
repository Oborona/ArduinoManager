#ifndef DATAINDICATOR_H
#define DATAINDICATOR_H

#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QPainter>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QTextStream>

#include "comthread.h"

class DataIndicator : public QWidget
{
    Q_OBJECT

private:
    QString name;
    QString title;
    float temp;
    float humidity;
    QFile* logFile;
    QTextStream* stream;

    float sx;
    float sy;

    QGridLayout* layout;
    ComThread* thread;
    int createLogfile();
    int counter;

protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);

public:
    explicit DataIndicator(QWidget *parent = nullptr);
    void setName(QString nn) { name = nn; }
    void setTitle(QString nt) { title = nt; }
//    void setFilename(QString nn) { logfileName = nn; }
    void setTemp(float nt) { temp = nt; }
    void setHumidity(float nh) { humidity = nh; }
    void connectWithThread(ComThread* nt);

signals:

public slots:
    void getData(QString data);

};

#endif // DATAINDICATOR_H
