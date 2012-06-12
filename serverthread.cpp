#include <QDataStream>
#include <QDebug>
#include "serverthread.h"


ServerThread::ServerThread(int descriptor, QObject *parent):QThread(parent)
{
    m_descriptor = descriptor;
    blockSize = 0;
}

void ServerThread::run()
{

    clientSocket = new QTcpSocket();
    if(!clientSocket->setSocketDescriptor(m_descriptor)) {
        qDebug("Socket error!");
        return;
    }
    connect(clientSocket,SIGNAL(readyRead()),this,SLOT(processReadyRead()));
    exec();
}

void ServerThread::processReadyRead()
{
    qDebug("message arrive..");
    QString messageType;
    QDataStream in(clientSocket);


    in.setVersion(QDataStream::Qt_4_7);
    if(blockSize == 0) {
        if(clientSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> blockSize;
        qDebug()<<"block size: "<<blockSize;
    }

    if(clientSocket->bytesAvailable() < blockSize)
        return;
    in >> messageType;

    //verify the user name and password,write back the result
    if(messageType == "Verify") {
        QString userName;
        QString password;
        QByteArray block;
        QDataStream out(&block,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_7);

        in >> userName >> password;
        if(userName == "potato" && password == "123"){
            out << quint16(0) << QString("True");

        }else {
            out << quint16(0) << QString("False");
        }
        out.device()->seek(0);
        out << quint16(block.size() - sizeof(quint16));

        clientSocket->write(block);
    }

}
