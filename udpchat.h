#ifndef UDPCHAT_H
#define UDPCHAT_H

#include <QObject>
#include "userdm.h"
class QUdpSocket;
class QHostAddress;

class UdpChat:public QObject
{
    Q_OBJECT

public:
    UdpChat(QObject *parent = 0);
    void startWork(quint16 port);

private slots:
    void processReadyRead();
    void processUserOffline(const QString& userName);


private:
    QUdpSocket *udpSocket;

    void processDatagram(QByteArray block,QHostAddress &sender,quint16 port);
    void processLogin(QDataStream &in, QHostAddress &sender,quint16 port);
    void processLogout();
    void processBroadcastMessage(QDataStream &in);
    void sendDatagram(const QString &msgType,const QString &msg,const QString &ip,quint16 port);
};

#endif // UDPCHAT_H
