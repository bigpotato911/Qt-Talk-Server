#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>

class TcpThread : public QThread
{
    Q_OBJECT
public:
    explicit TcpThread(QObject *parent = 0);

    void run();


};

#endif // SERVERTHREAD_H
