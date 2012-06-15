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

signals:
    void userOffline(const QString &userName);
public slots:
    void processReadyRead();
    void processUserOffline();
private:

    void processVerify(QDataStream &in);

    QString m_userName;
    int m_descriptor;
    QTcpSocket *tcpSocket;
    quint16 blockSize;

};

#endif // TCPCONNECTION_H
