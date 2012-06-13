#include <QDataStream>
#include <QDebug>
#include "tcpthread.h"


TcpThread::TcpThread(QObject *parent):QThread(parent)
{

}

void TcpThread::run()
{
    exec();

}

