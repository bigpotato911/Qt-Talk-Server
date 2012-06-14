#ifndef DBHELPER_H
#define DBHELPER_H

#include <QSqlDatabase>

class DBHelper
{


public:
    static bool createConnection();
    static void close();
private:
    DBHelper();

    static QSqlDatabase db;
    static QString hostName;
    static QString databaseName;
    static QString userName;
    static QString password;



};

#endif // DBHELPER_H
