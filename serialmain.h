/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */
#ifndef SERIALMAIN_H
#define SERIALMAIN_H

#include "qextserialport.h"
#include <QString>
#include <QObject>
#include <QtCore>


class SerialMain : public QObject
{
    Q_OBJECT

public:
    SerialMain(QString portName="/dev/ttyUSB0", QObject *parent = 0);
    ~SerialMain();


private:
    QextSerialPort *port;

    QString message;

    void transmitMsg();
    void receiveMsg();
    void appendCR();
    void appendLF();
    void closePort();
    void openPort();


signals:
    void dataReceived(const QByteArray&);

private slots:

    void onReadyRead();
};

#endif // SERIALMAIN_H
