#include <QtCore/QCoreApplication>
#include <QTcpServer>
#include "server.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    Server server;
    if(!server.listen(QHostAddress::Any,9999)) {
        qCritical("Cannot listen to port 9999");
        return 1;
    }

    return a.exec();
}
