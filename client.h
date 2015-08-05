/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */

#ifndef CLIENT_H
#define CLIENT_H


#include <QTcpSocket>






class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QString NetworkAddr,QObject *parent = 0);
    void sendText(QString text);
    
public slots:
    void connectToServer();
    void disconnectFromServer();
    void readServer();
    void displayError(QAbstractSocket::SocketError socketError);
    void sendMSG();
    void sendKey(int key);


signals:
    void dataReceived(QByteArray);

private:

    QTcpSocket *tcpSocket;    
 //   QString currentString;
    quint16 blockSize;
    QString m_NetworkAddr;



    
};

#endif // CLIENT_H
