#include "dataindicator.h"

DataIndicator::DataIndicator(QWidget *parent) : QWidget(parent)
{
    temp = 0;
    humidity = 0;
    counter = 0;
    this->resize(200, 200);
}

int DataIndicator::createLogfile()
{
    if (title.isEmpty())
    {
        qDebug() << "Cannot create logfile for " << title;
        return 0;
    }

    QDir dir(QApplication::applicationDirPath() + "/logs");
    if (!dir.exists())
    {
        qDebug() << dir.path();
        if (!dir.mkdir(dir.path()))
        {
            qDebug() << "Cannot create logdir";
            return 0;
        }
    }

    QString logfileName = dir.path();
    logfileName += QDateTime::currentDateTime().toString("/yyyy.MM.dd-hh_mm_ss-");
    logfileName += title;
    logfileName += ".log";
    qDebug() << logfileName;

    logFile = new QFile(logfileName);
    logFile->open(QIODevice::WriteOnly);
    stream = new QTextStream(logFile);
    return 1;
}

void DataIndicator::paintEvent(QPaintEvent *event)
{
    sx = this->width();
    sy = this->height();

    Q_UNUSED(event)
    QPainter painter(this);

    painter.setBrush(Qt::white);
    painter.drawRect(0, 0, sx, sy);
    painter.setBrush(Qt::black);
    painter.drawRect(sx*0.02, sy*0.02, sx*0.96, sy*0.96);
    painter.setBrush(Qt::white);
    painter.drawRect(sx*0.05, sy*0.05, sx*0.9, sy*0.9);

    QPen pen(Qt::black, sx*0.02);
    painter.setPen(pen);
    painter.setBrush(Qt::cyan);
    painter.drawRect(sx*0.10, sy*0.40, sx*0.7, sy*0.5);
    painter.setBrush(Qt::white);
    painter.drawRect(sx*0.25, sy*0.40, sx*0.07, sy*0.07);
    painter.drawRect(sx*0.25, sy*0.83, sx*0.07, sy*0.07);

    QFont font;
    font.setPixelSize(sx*0.15);
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.drawText(sx*0.1, sy*0.26, title);

    float datax = sx*0.36;
    float datay = sy*0.45;

    pen.setColor(Qt::black);
    pen.setWidth(sx*0.02);
    painter.setPen(pen);
    painter.setBrush(Qt::white);
    painter.drawRect(datax, datay, sx*0.55, sy*0.40);

    font.setPixelSize(sx*0.14);
    painter.setFont(font);
    painter.drawText(datax+sx*0.08, sy*0.60, QString("%1%").arg(temp, 0, 'f', 2));
    painter.drawText(datax+sx*0.08, sy*0.80, QString("%1C").arg(humidity, 0, 'f', 2));

    painter.setBrush(Qt::white);
    painter.drawEllipse(sx*0.13, sy*0.54, sx*0.2, sy*0.2);
    if (counter%2 == 0)
        painter.drawLine(sx*0.13, sy*0.64, sx*0.33, sy*0.64);
    else
        painter.drawLine(sx*0.23, sy*0.54, sx*0.23, sy*0.74);
    counter++;
}

void DataIndicator::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    sx = this->width();
    sy = this->height();
    this->update();
}

void DataIndicator::connectWithThread(ComThread* nt)
{
    thread = nt;
    this->setName(thread->getName());
    connect(thread, SIGNAL(sendData(QString)), this, SLOT(getData(QString)));
    createLogfile();
}

void DataIndicator::getData(QString data)
{
//    qDebug() << name << data;
    QStringList strl = data.split(" ");
    if (strl.size() > 0)
    {
        if (strl.size() > 1)
        {
            this->setTemp(strl.at(0).toFloat());
            this->setHumidity(strl.at(1).toFloat());
            *stream << QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss ");
            *stream << strl.at(0) << " "
                   << strl.at(1) << Qt::endl;
            stream->flush();
        }
    }
    this->update();
}

