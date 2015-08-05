/*
 * (c) by Daniel Pelikan 2013,2014,2015
 */
#include "client.h"

#include <QtGui>
#include <QtNetwork>

#include <iostream>


Client::Client(QString NetworkAddr,QObject *parent) :
    m_NetworkAddr(NetworkAddr),QObject(parent)
{



    tcpSocket = new QTcpSocket(this);

 //   connect(connectButton,SIGNAL(clicked()),this,SLOT(connectToServer()));
 //   connect(sendButton,SIGNAL(clicked()),this,SLOT(sendMSG()));
 //   connect(disconnectButton,SIGNAL(clicked()),this,SLOT(disconnectFromServer()));
//    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readServer()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));



 //   connect(controller,SIGNAL(sendKey(int)),this,SLOT(sendKey(int)));


    connectToServer();
}

void Client::connectToServer(){
    blockSize=0;
    tcpSocket->abort();

    QString IPAddr=m_NetworkAddr.section(":", 0,0);
    QString Port=m_NetworkAddr.section(":", 1,1);

    std::cout<<"IP: "<<IPAddr.toStdString()<<"\t Port: "<<Port.toStdString()<<std::endl;

    tcpSocket->connectToHost(IPAddr,Port.toInt());
}

void Client::disconnectFromServer(){
    tcpSocket->close();
}

void Client::readServer(){


    QByteArray data;
    if(tcpSocket->bytesAvailable()) {
                //here i needed a string..
          //QString line = QString::fromUtf8(tcpSocket->readLine()).trimmed();
          //std::cout<<"readServer():"<<line.toStdString()<<std::endl;

       //   recivedTextEdit->setTextColor(QColor(0, 0, 255, 255));
       //   recivedTextEdit->append(line);
       data=tcpSocket->readAll();
    }

    emit dataReceived(data);



  //  statusLabel->setText(currentTime);
  //  getTimeButton->setEnabled(true);

}



void Client::displayError(QAbstractSocket::SocketError socketError){
    QString msg;
    switch(socketError){
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            msg.append("Host not found");
            break;
        case QAbstractSocket::ConnectionRefusedError:
            msg.append("Connection rejected");
            break;
        default:
        msg.append(tr("Error %1").arg(tcpSocket->errorString()));
    }

    if(!msg.isEmpty()){
        std::cerr<<"There was an error"<<std::endl;
    }
        //QMessageBox::information(this,"Client",msg);



   // connectButton->setEnabled(true);

}



void Client::sendMSG(){
    QString text;// = sendTextEdit->toPlainText();
   // recivedTextEdit->setTextColor(QColor(255, 0, 0, 127));
   // recivedTextEdit->append(text);
    //sendTextEdit->clear();

    sendText(text);
}

void Client::sendText(QString text){
 /*   QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out<<(quint16)0;

    QString data;
    data.append(text);

    out<<data;

    out.device()->seek(0);

    out <<(quint16)(block.size() - sizeof(quint16));

    std::cout<<"sendText()"<<text.toStdString()<<std::endl;

    tcpSocket->write(block);
    tcpSocket->flush();

*/

    tcpSocket->write(text.toUtf8());
    tcpSocket->write("\n");

}

void Client::sendKey(int key){

    /*This will be fixed in a smaert way Testing only*/


    if(key==Qt::Key_Up){
        sendText(QString("Serial=KEY UP"));
    }
    else if(key==Qt::Key_Down){
        sendText(QString("Serial=KEY DOWN"));
    }
    else if(key==Qt::Key_Right){
        sendText(QString("Serial=KEY RIGHT"));
    }
    else if(key==Qt::Key_Left){
        sendText(QString("Serial=KEY LEFT"));
    }
    else if(key==Qt::Key_Space){
        sendText(QString("Serial=KEY BREAK"));
    }
    else{
        std::cerr<<"Wrong key"<<std::endl;
    }


    sendText(QString("Key="+QString::number(key)));
}

