#include <QDebug>
#include "tcpsocketserver.h"
#include "tcpthread.h"
#include "tcpconnection.h"
TcpSocketServer::TcpSocketServer() :
    QTcpServer()
{
}

void TcpSocketServer::incomingConnection(int descriptor)
{
    qDebug("new connection...");
    TcpThread *tcpThread = new TcpThread();
    TcpConnection *tcpConnection = new TcpConnection(descriptor);
    tcpConnection->moveToThread(tcpThread);

    connect(tcpThread,SIGNAL(finished()),tcpThread,SLOT(deleteLater()));
    tcpThread->start();

}
