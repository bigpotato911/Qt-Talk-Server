#include "user.h"

User::User()
{
}

QString User::name()
{
    return m_name;
}

QString User::ip()
{
    return m_ip;
}

quint16 User::port()
{
    return m_port;
}

void User::setName(const QString &name)
{
    m_name = name;
}

void User::setIp(const QString &ip)
{
    m_ip = ip;
}


void User::setPort(quint16 port)
{
    m_port = port;
}
