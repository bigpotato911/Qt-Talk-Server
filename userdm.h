#ifndef USERDM_H
#define USERDM_H
#include <QList>
#include "user.h"
class QSqlQuery;
class UserDM
{
private:
    UserDM();


public:
    static UserDM &getInstance();
    static QList<User> getOnlineUsers();
    static QString getPwdFromName(QString userName);
    void static setUserOnline(const QString &userName,const QString &ip,quint16 port);
    void static setUserOffline(const QString &userName);
    void static close();

};

#endif // USERDM_H
