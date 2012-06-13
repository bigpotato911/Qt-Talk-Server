#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QObject>
class QTcpSocket;
class QDataStream;

class TcpConnection : public QObject
{
    Q_OBJECT
public:
    explicit TcpConnection(int descriptor,QObject *parent = 0);

    
public slots:
    void processReadyRead();

private:

    int m_descriptor;
    QTcpSocket *tcpSocket;
    quint16 blockSize;

    void processVerify(QDataStream &in);

};

#endif // TCPCONNECTION_H
