#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include "dbhelper.h"

QSqlDatabase DBHelper::db = QSqlDatabase::addDatabase("QMYSQL");
DBHelper::DBHelper()
{
}

void DBHelper::close()
{
    db.close();
}

bool DBHelper::createConnection()
{

    db.setHostName(hostName);
    db.setDatabaseName(databaseName);
    db.setUserName(userName);
    db.setPassword(password);
    if(!db.open()) {
        qCritical() << "database error:" << db.lastError().text();
        return false;
    }
    return true;
}

QString DBHelper::hostName = "127.0.0.1";
QString DBHelper::databaseName = "qt_chat";
QString DBHelper::userName = "root";
QString DBHelper::password = "ubuntu";
