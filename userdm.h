#ifndef USERDM_H
#define USERDM_H
#include <QList>
class QSqlQuery;
class UserDM
{
private:
    UserDM();


public:
    static UserDM &getInstance();
    static QList<QString> getOnlineUsers();
    static QString getPwdFromName(QString userName);
    void static setUserOnline(QString userName);
    void static setUserOffline(QString userName);
    void static close();

};

#endif // USERDM_H
