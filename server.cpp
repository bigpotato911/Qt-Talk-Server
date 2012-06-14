#include "server.h"
#include "udpchat.h"
#include "tcpsocketserver.h"
Server::Server()
{
    TcpSocketServer *tcpSocketServer = new TcpSocketServer();
    if(!tcpSocketServer->listen(QHostAddress::Any,9998)) {
        qCritical("Cannot listen to port 9998");

    } else {
        UdpChat *udpChat = new UdpChat();
        udpChat->startWork(9999);

    }
}
