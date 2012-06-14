#ifndef UDPCHAT_H
#define UDPCHAT_H

#include <QObject>
#include "userdm.h"
class QUdpSocket;
class QHostAddress;

class UdpChat:public QObject
{
    Q_OBJECT
private slots:
    void processReadyRead();
public:
    UdpChat(QObject *parent = 0);
    void startWork(quint16 port);

private:
    QUdpSocket *udpSocket;

    void processDatagram(QByteArray block,QHostAddress &sender,quint16 port);
    void processLogin(QHostAddress &sender,quint16 port);
    void processLogout();
    void processChat();
};

#endif // UDPCHAT_H
