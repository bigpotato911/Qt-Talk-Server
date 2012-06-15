#include <QUdpSocket>
#include <QHostAddress>
#include <QDataStream>
#include <QStringList>

#include "user.h"
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



void UdpChat::processDatagram(QByteArray block, QHostAddress &sender, quint16 port)
{
    QDataStream in(&block,QIODevice::ReadOnly);
    QString messageType;
    in >> messageType;
    if(messageType == "Login") {
        processLogin(in,sender,port);
    } else if(messageType == "BroadcastMessage") {
        processBroadcastMessage(in);
    }
}

void UdpChat::processLogin(QDataStream &in,QHostAddress &sender, quint16 port)
{
    qDebug("process login");
    QString loginName;
    in >> loginName;
    UserDM::setUserOnline(loginName,sender.toString(),port);
    QList<User> onlineUsers = UserDM::getOnlineUsers();
    UserDM::close();

    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);  
    out.setVersion(QDataStream::Qt_4_7);
    QStringList onlineUserNames;
    for(int i = 0;i < onlineUsers.size();i++) {
        User user = onlineUsers[i];
        onlineUserNames << user.name();
        if(user.name() != loginName) {
            QString user_ip = user.ip();
            quint16 user_port = user.port();
            //sendDatagram(QString("UserLogin"),loginName,user_ip,user_port);
            QByteArray buffer;
            QDataStream broadcast_out(&buffer,QIODevice::WriteOnly);
            broadcast_out.setVersion(QDataStream::Qt_4_7);
            broadcast_out << QString("NewUserLogin") << loginName;
            udpSocket->writeDatagram(buffer,QHostAddress(user_ip),user_port);
        }
    }
    out << QString("ShowOnlineUsers") << onlineUserNames;
    udpSocket->writeDatagram(block,sender,port);


}

void UdpChat::processBroadcastMessage(QDataStream &in)
{
    QString sendUserName;
    QString time;
    QString message;
    in >> sendUserName >> time >> message;

    QList<User> onlineUsers = UserDM::getOnlineUsers();
    UserDM::close();

    for(int i = 0;i < onlineUsers.size();i++) {
        User user = onlineUsers[i];


        QString user_ip = user.ip();
        quint16 user_port = user.port();

        QByteArray buffer;
        QDataStream broadcast_out(&buffer,QIODevice::WriteOnly);
        broadcast_out.setVersion(QDataStream::Qt_4_7);
        broadcast_out << QString("NewBroadcaseMessage") << sendUserName << time << message;
        udpSocket->writeDatagram(buffer,QHostAddress(user_ip),user_port);
     }

}

void UdpChat::processUserOffline(const QString &userName)
{
    qDebug("process user offline");
    QList<User> onlineUsers = UserDM::getOnlineUsers();
    UserDM::close();

    for(int i = 0;i < onlineUsers.size();i++) {
        User user = onlineUsers[i];

        QString user_ip = user.ip();
        quint16 user_port = user.port();

        QByteArray buffer;
        QDataStream broadcast_out(&buffer,QIODevice::WriteOnly);
        broadcast_out.setVersion(QDataStream::Qt_4_7);
        broadcast_out << QString("UserOffline") << userName;
        udpSocket->writeDatagram(buffer,QHostAddress(user_ip),user_port);
     }
}

void UdpChat::sendDatagram(const QString &msgType, const QString &msg, const QString &ip, quint16 port)
{

}


