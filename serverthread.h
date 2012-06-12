#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>

class ServerThread : public QThread
{
    Q_OBJECT
public:
    explicit ServerThread(int descriptor,QObject *parent = 0);

    void run();
public slots:
    void processReadyRead();
private:
    int m_descriptor;
    QTcpSocket *clientSocket;
    quint16 blockSize;
    
};

#endif // SERVERTHREAD_H
