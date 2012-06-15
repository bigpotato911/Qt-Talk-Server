#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User();
    QString name();
    QString ip();
    quint16 port();

    void setName(const QString &name);
    void setIp(const QString &ip);
    void setPort(quint16 port);

private:
    QString m_name;
    QString m_ip;
    quint16 m_port;
};

#endif // USER_H
