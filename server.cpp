#include <QDebug>
#include "server.h"
#include "tcpthread.h"
#include "tcpconnection.h"
Server::Server() :
    QTcpServer()
{
}

void Server::incomingConnection(int descriptor)
{
    qDebug("new connection...");
    TcpThread *tcpThread = new TcpThread();
    TcpConnection *tcpConnection = new TcpConnection(descriptor);
    tcpConnection->moveToThread(tcpThread);

    connect(tcpThread,SIGNAL(finished()),tcpThread,SLOT(deleteLater()));
    tcpThread->start();
}
