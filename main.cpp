#include <QtCore/QCoreApplication>
#include <QObject>
#include <QTcpServer>

#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;

    return a.exec();
}
