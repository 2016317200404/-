#ifndef DATABASETOOL_H
#define DATABASETOOL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class DatabaseTool
{
public:
    static DatabaseTool& GetInstance();

    QString serachRecord(int matchesID, QString occupation_1, QString occupation_2, QString Moves_1_1, QString Moves_1_2, QString Moves_1_3, QString Moves_2_1, QString Moves_2_2, QString Moves_2_3);

    int addInfo(int matchesID, QString occupation_1, QString occupation_2, QString Moves_1_1, QString Moves_1_2, QString Moves_1_3, QString Moves_2_1, QString Moves_2_2, QString Moves_2_3, int result);

    QStringList serachMoves(int matchesID, QString occupation);

private:
    DatabaseTool();
    ~DatabaseTool();

private:
    QSqlDatabase db;
};

#endif // DATABASETOOL_H
