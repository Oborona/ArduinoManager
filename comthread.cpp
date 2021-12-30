#include "comthread.h"

ComThread::ComThread(QString n)
{
    name = n;
}

void ComThread::setup()
{
    //LPCTSTR portName = name.toStdWString().c_str();
    //LPCTSTR portName = L"COM6";//= (LPCTSTR)name.toStdString().c_str();
    hSerial = ::CreateFile(portName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if(hSerial == INVALID_HANDLE_VALUE)
    {
            if(GetLastError()==ERROR_FILE_NOT_FOUND)
        {
            emit sendError(name, "Serial port does not exist.");
        }
        emit sendError(name, "Some other error occurred.");
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        emit sendError(name, "getting state error");
    }
    dcbSerialParams.BaudRate=CBR_9600;
    dcbSerialParams.ByteSize=8;
    dcbSerialParams.StopBits=ONESTOPBIT;
    dcbSerialParams.Parity=NOPARITY;
    if(!SetCommState(hSerial, &dcbSerialParams))
    {
        emit sendError(name, "error setting serial port state");
    }
}

void ComThread::run()
{
    QString data;
    DWORD iSize;
    char sReceivedChar;
    while (true)
    {
          ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);  // получаем 1 байт
          if (iSize > 0)   // если что-то принято, выводим
              data.append(sReceivedChar);
          if (data.contains("C"))
          {
              emit sendData(name, data);
//              qDebug() << data.simplified();
              data.clear();
          }
    }

}
