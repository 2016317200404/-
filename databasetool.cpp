#include "databasetool.h"
#include <QString>

DatabaseTool& DatabaseTool::GetInstance() {
    static DatabaseTool databaseTool;
    return databaseTool;
}

QString DatabaseTool::serachRecord(int matchesID, QString occupation_1, QString occupation_2, QString Moves_1_1, QString Moves_1_2, QString Moves_1_3, QString Moves_2_1, QString Moves_2_2, QString Moves_2_3)
{
    QString queryString = "SELECT occupation_1,Number_Of_Wins,count_win"
                          " FROM [record table]"
                          " where matchesID ='%1' "
                          " and (occupation_1 = '%2'"
                          " and occupation_2 = '%3'"
                          " and ((Moves_1_1 = '%4' and ((Moves_1_2 = '%5' and Moves_1_3 = '%6') or  (Moves_1_2 = '%6' and Moves_1_3 = '%5')))"
                          " or (Moves_1_1 = '%5' and ((Moves_1_2 = '%4' and Moves_1_3 = '%6') or  (Moves_1_2 = '%6' and Moves_1_3 = '%4')))"
                          " or (Moves_1_1 = '%6' and ((Moves_1_2 = '%4' and Moves_1_3 = '%5') or  (Moves_1_2 = '%5' and Moves_1_3 = '%4'))))"
                          " and ((Moves_2_1 = '%7' and ((Moves_2_2 = '%8' and Moves_2_3 = '%9') or  (Moves_2_2 = '%9' and Moves_2_3 = '%8')))"
                          " or (Moves_2_1 = '%8' and ((Moves_2_2 = '%7' and Moves_2_3 = '%9') or  (Moves_2_2 = '%9' and Moves_2_3 = '%7')))"
                          " or (Moves_2_1 = '%9' and ((Moves_2_2 = '%7' and Moves_2_3 = '%8') or  (Moves_2_2 = '%8' and Moves_2_3 = '%7')))) )   "
                          " or (occupation_1 = '%3'"
                          " and occupation_2 = '%2'"
                          " and ((Moves_1_1 = '%7' and ((Moves_1_2 = '%8' and Moves_1_3 = '%9') or  (Moves_1_2 = '%9' and Moves_1_3 = '%8')))"
                          " or (Moves_1_1 = '%8' and ((Moves_1_2 = '%7' and Moves_1_3 = '%9') or  (Moves_1_2 = '%9' and Moves_1_3 = '%7')))"
                          " or (Moves_1_1 = '%9' and ((Moves_1_2 = '%7' and Moves_1_3 = '%8') or  (Moves_1_2 = '%8' and Moves_1_3 = '%7'))))"
                          " and ((Moves_2_1 = '%4' and ((Moves_2_2 = '%5' and Moves_2_3 = '%6') or  (Moves_2_2 = '%6' and Moves_2_3 = '%5')))"
                          " or (Moves_2_1 = '%5' and ((Moves_2_2 = '%4' and Moves_2_3 = '%6') or  (Moves_2_2 = '%6' and Moves_2_3 = '%4')))"
                          " or (Moves_2_1 = '%6' and ((Moves_2_2 = '%4' and Moves_2_3 = '%5') or  (Moves_2_2 = '%5' and Moves_2_3 = '%4')))));";
    QString str = queryString.arg(matchesID).arg(occupation_1).arg(occupation_2).arg(Moves_1_1).arg(Moves_1_2).arg(Moves_1_3).arg(Moves_2_1).arg(Moves_2_2).arg(Moves_2_3);
    // qDebug() << str;
    if (db.open()) {
        QSqlQuery qry(db);
        qry.exec(str);
        if (qry.next()) {
            QString occupation = qry.value(0).toString();
            int count_win = qry.value(1).toInt();
            int count_match = qry.value(2).toInt();

            QString result = "记录次数%1, 胜率为%2";
            if (QString::compare(occupation_1, occupation, Qt::CaseSensitive) == 0) {
                float rate_win = (float)count_win / (float)count_match;
                return result.arg(count_match).arg(rate_win);
            } else {
                float rate_win = 1 - (float)count_win / (float)count_match;
                return result.arg(count_match).arg(rate_win);
            }
        } else {
            QString no_found = "数据库里没有该数据，请添加";
            return no_found;
        }
    }
    return QString("数据库未连接");
}

int DatabaseTool::addInfo(int matchesID, QString occupation_1, QString occupation_2, QString Moves_1_1, QString Moves_1_2, QString Moves_1_3, QString Moves_2_1, QString Moves_2_2, QString Moves_2_3, int result)
{
    QString queryString = "SELECT occupation_1,Number_Of_Wins,count_win"
                          " FROM [record table]"
                          " where matchesID =\"%1\" "
                          " and (occupation_1 = \"%2\""
                          " and occupation_2 = \"%3\""
                          " and ((Moves_1_1 = \"%4\" and ((Moves_1_2 = \"%5\" and Moves_1_3 = \"%6\") or  (Moves_1_2 = \"%6\" and Moves_1_3 = \"%5\")))"
                          " or (Moves_1_1 = \"%5\" and ((Moves_1_2 = \"%4\" and Moves_1_3 = \"6\") or  (Moves_1_2 = \"%6\" and Moves_1_3 = \"%4\")))"
                          " or (Moves_1_1 = \"%6\" and ((Moves_1_2 = \"%4\" and Moves_1_3 = \"%5\") or  (Moves_1_2 = \"%5\" and Moves_1_3 = \"%4\"))))"
                          " and ((Moves_2_1 = \"%7\" and ((Moves_2_2 = \"%8\" and Moves_2_3 = \"%9\") or  (Moves_2_2 = \"%9\" and Moves_2_3 = \"%8\")))"
                          " or (Moves_2_1 = \"%8\" and ((Moves_2_2 = \"%7\" and Moves_2_3 = \"%9\") or  (Moves_2_2 = \"%9\" and Moves_2_3 = \"%7\")))"
                          " or (Moves_2_1 = \"%9\" and ((Moves_2_2 = \"%7\" and Moves_2_3 = \"%8\") or  (Moves_2_2 = \"%8\" and Moves_2_3 = \"%7\")))) )   "
                          " or (occupation_1 = \"%3\""
                          " and occupation_2 = \"%2\""
                          " and ((Moves_1_1 = \"%7\" and ((Moves_1_2 = \"%8\" and Moves_1_3 = \"%9\") or  (Moves_1_2 = \"%9\" and Moves_1_3 = \"%8\")))"
                          " or (Moves_1_1 = \"%8\" and ((Moves_1_2 = \"%7\" and Moves_1_3 = \"%9\") or  (Moves_1_2 = \"%9\" and Moves_1_3 = \"%7\")))"
                          " or (Moves_1_1 = \"%9\" and ((Moves_1_2 = \"%7\" and Moves_1_3 = \"%8\") or  (Moves_1_2 = \"%8\" and Moves_1_3 = \"%7\"))))"
                          " and ((Moves_2_1 = \"%4\" and ((Moves_2_2 = \"%5\" and Moves_2_3 = \"%6\") or  (Moves_2_2 = \"%6\" and Moves_2_3 = \"%5\")))"
                          " or (Moves_2_1 = \"%5\" and ((Moves_2_2 = \"%4\" and Moves_2_3 = \"%6\") or  (Moves_2_2 = \"%6\" and Moves_2_3 = \"%4\")))"
                          " or (Moves_2_1 = \"%6\" and ((Moves_2_2 = \"%4\" and Moves_2_3 = \"%5\") or  (Moves_2_2 = \"%5\" and Moves_2_3 = \"%4\")))));";
    QString str = queryString.arg(matchesID).arg(occupation_1).arg(occupation_2).arg(Moves_1_1).arg(Moves_1_2).arg(Moves_1_3).arg(Moves_2_1).arg(Moves_2_2).arg(Moves_2_3);
    // qDebug() << str;
    if (db.open()) {
        QSqlQuery qry(db);
        //数据库里有数据
        qry.exec(str);
        if (qry.next()) {
            QString occupation = qry.value(0).toString();
            int count_win = qry.value(1).toInt();
            int count_match = qry.value(2).toInt();

            count_match++;
            QString updateString = "UPDATE [record table]"
                                  " SET Number_Of_Wins =\"%10\",count_win =\"%11\" "
                                  " where matchesID =\"%1\" "
                                  " and (occupation_1 = \"%2\""
                                  " and occupation_2 = \"%3\""
                                  " and ((Moves_1_1 = \"%4\" and ((Moves_1_2 = \"%5\" and Moves_1_3 = \"%6\") or  (Moves_1_2 = \"%6\" and Moves_1_3 = \"%5\")))"
                                  " or (Moves_1_1 = \"%5\" and ((Moves_1_2 = \"%4\" and Moves_1_3 = \"6\") or  (Moves_1_2 = \"%6\" and Moves_1_3 = \"%4\")))"
                                  " or (Moves_1_1 = \"%6\" and ((Moves_1_2 = \"%4\" and Moves_1_3 = \"%5\") or  (Moves_1_2 = \"%5\" and Moves_1_3 = \"%4\"))))"
                                  " and ((Moves_2_1 = \"%7\" and ((Moves_2_2 = \"%8\" and Moves_2_3 = \"%9\") or  (Moves_2_2 = \"%9\" and Moves_2_3 = \"%8\")))"
                                  " or (Moves_2_1 = \"%8\" and ((Moves_2_2 = \"%7\" and Moves_2_3 = \"%9\") or  (Moves_2_2 = \"%9\" and Moves_2_3 = \"%7\")))"
                                  " or (Moves_2_1 = \"%9\" and ((Moves_2_2 = \"%7\" and Moves_2_3 = \"%8\") or  (Moves_2_2 = \"%8\" and Moves_2_3 = \"%7\")))) )   "
                                  " or (occupation_1 = \"%3\""
                                  " and occupation_2 = \"%2\""
                                  " and ((Moves_1_1 = \"%7\" and ((Moves_1_2 = \"%8\" and Moves_1_3 = \"%9\") or  (Moves_1_2 = \"%9\" and Moves_1_3 = \"%8\")))"
                                  " or (Moves_1_1 = \"%8\" and ((Moves_1_2 = \"%7\" and Moves_1_3 = \"%9\") or  (Moves_1_2 = \"%9\" and Moves_1_3 = \"%7\")))"
                                  " or (Moves_1_1 = \"%9\" and ((Moves_1_2 = \"%7\" and Moves_1_3 = \"%8\") or  (Moves_1_2 = \"%8\" and Moves_1_3 = \"%7\"))))"
                                  " and ((Moves_2_1 = \"%4\" and ((Moves_2_2 = \"%5\" and Moves_2_3 = \"%6\") or  (Moves_2_2 = \"%6\" and Moves_2_3 = \"%5\")))"
                                  " or (Moves_2_1 = \"%5\" and ((Moves_2_2 = \"%4\" and Moves_2_3 = \"%6\") or  (Moves_2_2 = \"%6\" and Moves_2_3 = \"%4\")))"
                                  " or (Moves_2_1 = \"%6\" and ((Moves_2_2 = \"%4\" and Moves_2_3 = \"%5\") or  (Moves_2_2 = \"%5\" and Moves_2_3 = \"%4\")))));";
            if (QString::compare(occupation_1, occupation, Qt::CaseSensitive) == 0) {
                if (result != 0) {
                    count_win++;
                }
            } else {
                if (result == 0) {
                    count_win++;
                }
            }
            QString tempStr = updateString.arg(matchesID).arg(occupation_1).arg(occupation_2).arg(Moves_1_1).arg(Moves_1_2).arg(Moves_1_3).arg(Moves_2_1).arg(Moves_2_2).arg(Moves_2_3).arg(count_win).arg(count_match);
            qry.exec(tempStr);
        } else {
            QString insertString = "INSERT INTO [record table] VALUES ('%1','%2', '%3','%4','%5','%6','%7','%8','%9','%10','%11','%12')";
            if (qry.exec("SELECT COUNT(*) From [record table]") ) {
                qry.next();
                int ID = qry.value(0).toInt();
                ID++;
                QString tempStr = insertString.arg(ID).arg(matchesID).arg(occupation_1).arg(occupation_2).arg(Moves_1_1).arg(Moves_2_1).arg(Moves_1_2).arg(Moves_2_2).arg(Moves_1_3).arg(Moves_2_3).arg(result).arg(1);
                qry.exec(tempStr);
            }
        }
        return 1;
    }
    return 0;
}

QStringList DatabaseTool::serachMoves(int matchesID, QString occupation)
{
    QStringList resultList;
    QString qeyMoves = "WITH CombinedMoves AS ("
                       " SELECT"
                       " CASE"
                       " WHEN occupation_1 = '%1' THEN Moves_1_1"
                       " ELSE Moves_2_1"
                       " END AS Moves_1_1,"
                       " CASE"
                       " WHEN occupation_1 = '%1' THEN Moves_1_2"
                       " ELSE Moves_2_2"
                       " END AS Moves_1_2,"
                       " CASE"
                       " WHEN occupation_1 = '%1' THEN Moves_1_3"
                       " ELSE Moves_2_3"
                       " END AS Moves_1_3"
                       " FROM"
                       " [record table]"
                       " WHERE"
                       " (occupation_1 = '%1' OR occupation_2 = '%1') and matchesID ='%2'"
                       " ),"
                       " UniqueMoves AS ("
                       " SELECT DISTINCT Moves_1_1 AS move FROM CombinedMoves"
                       " UNION"
                       " SELECT DISTINCT Moves_1_2 AS move FROM CombinedMoves"
                       " UNION"
                       " SELECT DISTINCT Moves_1_3 AS move FROM CombinedMoves"
                       " )"
                       " SELECT move"
                       " FROM UniqueMoves"
                       " ORDER BY move;";
    QString str = qeyMoves.arg(occupation).arg(matchesID);
    if (db.open()) {
        QSqlQuery qry(db);
        if (qry.exec(str)) {
            while (qry.next()) {
                resultList.append(qry.value(0).toString());
            }
        }
    }
    return resultList;
}

DatabaseTool::DatabaseTool(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("guess2.db");

    if (!db.open()) {
        qDebug() << "Error: Unable to open database";
        return;
    }

    qDebug() << "Database opened successfully";
}

DatabaseTool::~DatabaseTool()
{
    if (db.open()) {
        db.close();
        qDebug() << "DataBase close successfully";
    }
}
