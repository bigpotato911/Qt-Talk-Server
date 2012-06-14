#include <QTcpSocket>
#include <QDataStream>
#include "tcpconnection.h"
#include "userdm.h"

TcpConnection::TcpConnection(int descriptor, QObject *parent) :
    QObject(parent)
{
    m_descriptor = descriptor;
    UserDM::getInstance();
    tcpSocket = new QTcpSocket(this);
    if(!tcpSocket->setSocketDescriptor(m_descriptor)){
        qCritical("Socket error");
    }
    blockSize = 0;
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(processReadyRead()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(processUserOffline()));
}

void TcpConnection::processReadyRead()
{
    qDebug("message arrive..");
    QString messageType;
    QDataStream in(tcpSocket);


    in.setVersion(QDataStream::Qt_4_7);
    if(blockSize == 0) {
        if(tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> blockSize;
        qDebug()<<"block size: "<<blockSize;
    }

    if(tcpSocket->bytesAvailable() < blockSize)
        return;
    in >> messageType;

    //verify the user name and password,write back the result
    if(messageType == "Verify") {
        processVerify(in);

    }

}

void TcpConnection::processVerify(QDataStream &in)
{
    QString userName;
    QString password;
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_4_7);

    in >> userName >> password;
    QString pwdFromDatabase = UserDM::getPwdFromName(userName);
    qDebug() <<"pwd from database:" << pwdFromDatabase;
    if(password == pwdFromDatabase){
        m_userName = userName;
        out << quint16(0) << QString("True");
        UserDM::setUserOnline(userName);

    }else {
        out << quint16(0) << QString("False");
    }
    UserDM::close();
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    tcpSocket->write(block);

}

void TcpConnection::processUserOffline()
{
    UserDM::setUserOffline(m_userName);
    UserDM::close();
}

