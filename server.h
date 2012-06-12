#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    
protected:
    void incomingConnection(int descriptor);
    
};

#endif // SERVER_H
