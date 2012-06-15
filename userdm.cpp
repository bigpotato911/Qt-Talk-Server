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



QList<User> UserDM::getOnlineUsers()
{
    QList<User> onlineUsers;
    if(DBHelper::createConnection()) {

        QSqlQuery query;
        QString userName;
        QString ip;
        quint16 port;
        query.exec("select name,ip,port from user where online = 1");
        while(query.next()) {

            userName= query.value(0).toString();
            ip = query.value(1).toString();
            port = query.value(2).toUInt();

            User user;
            user.setName(userName);
            user.setIp(ip);
            user.setPort(port);
            onlineUsers.push_back(user);
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

void UserDM::setUserOnline(const QString &userName,const QString &ip,quint16 port)
{
    if(DBHelper::createConnection()) {
        QSqlQuery query;
        QString sql = "update user set online = 1,ip = '" + ip + "',port = " + QString::number(port)+" where name = '" + userName + "'";
        query.exec(sql);
    }
}

void UserDM::setUserOffline(const QString &userName)
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

