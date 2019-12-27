#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

bool createConnection () {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database/database.s3db");
    if (!db.open())
        return false;
    return true;

}

#endif // DATABASE_H
