#include <QUdpSocket>
#include <QHostAddress>
#include <QDataStream>

#include "udpchat.h"

UdpChat::UdpChat(QObject *parent):QObject(parent)
{

    udpSocket = new QUdpSocket(this);
    UserDM::getInstance();

}

void UdpChat::startWork(quint16 port)
{
    if(!udpSocket->bind(QHostAddress::Any,port)) {
        qCritical() << "Udp socket error" <<udpSocket->errorString();
    }
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(processReadyRead()));

}

void UdpChat::processDatagram(QByteArray block, QHostAddress &sender, quint16 port)
{
    QDataStream in(&block,QIODevice::ReadOnly);
    QString messageType;
    in >> messageType;
    if(messageType == "Login") {
        processLogin(sender,port);
    } else if(messageType == "Logout") {
        processLogout();
    } else if(messageType == "Chat") {
        processChat();
    }
}

void UdpChat::processLogin(QHostAddress &sender, quint16 port)
{
    qDebug("process login");
    QList<QString> onlineUsers = UserDM::getOnlineUsers();
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    UserDM::close();
    out.setVersion(QDataStream::Qt_4_7);

    out << QString("ShowOnlineUsers") << onlineUsers;

    udpSocket->writeDatagram(block,sender,port);
}

void UdpChat::processLogout()
{
}

void UdpChat::processChat()
{
}

void UdpChat::processReadyRead()
{

    while(udpSocket->hasPendingDatagrams()) {
        QByteArray block;
        QHostAddress sender;
        quint16 port;
        block.resize(udpSocket->pendingDatagramSize());
        if(udpSocket->readDatagram(block.data(),block.size(),&sender,&port) == -1)
            continue;
        processDatagram(block,sender,port);

    }
}
