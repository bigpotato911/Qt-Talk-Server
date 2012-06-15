#ifndef TCP_SOCKET_SERVER_H
#define TCP_SOCKET_SERVER_H

#include <QTcpServer>

class TcpSocketServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpSocketServer();
signals:
    void userOffline(const QString &userName);
protected:
    void incomingConnection(int descriptor);
    
};

#endif // TCP_SOCKET_SERVER_H
