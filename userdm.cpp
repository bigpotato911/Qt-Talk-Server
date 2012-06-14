#include <QSqlQuery>
#include <QVariant>
#include <QString>
#include <QDebug>
#include "dbhelper.h"
#include "userdm.h"



UserDM::UserDM()
{

}

UserDM &UserDM::getInstance()
{
    UserDM instance;
    return instance;
}



QList<QString> UserDM::getOnlineUsers()
{
    QList<QString> onlineUsers;
    if(DBHelper::createConnection()) {

        QSqlQuery query;
        query.exec("select name from user where online = 1");
        while(query.next()) {
            QString onlineUser = query.value(0).toString();
            onlineUsers.push_back(onlineUser);
        }
        DBHelper::close();
    }

    return onlineUsers;
}

QString UserDM::getPwdFromName(QString userName)
{
    QString password;
    if(DBHelper::createConnection()) {
        QSqlQuery query;

        query.exec("select password from user where name = '" + userName + "'");
        query.addBindValue(userName);
        if(query.next()) {
            password = query.value(0).toString();
        }
        DBHelper::close();
    }

    return password;
}

void UserDM::setUserOnline(QString userName)
{
    if(DBHelper::createConnection()) {
        QSqlQuery query;
        query.exec("update user set online = 1 where name = '" + userName + "'");
        DBHelper::close();
    }
}

void UserDM::setUserOffline(QString userName)
{
    if(DBHelper::createConnection()) {
        QSqlQuery query;
        query.exec("update user set online = 0 where name = '" + userName + "'");
        DBHelper::close();
    }
}

void UserDM::close()
{
    DBHelper::close();
}

