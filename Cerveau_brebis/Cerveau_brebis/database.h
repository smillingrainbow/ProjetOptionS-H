#ifndef DATABASE_H
#define DATABASE_H

#include <QList>
#include <iostream>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QtSql/QSqlRecord>
#include <QMessageBox>
#include <iostream>

class Database
{
public:
    Database(){}
    ~Database(){}
    /**
     * @brief get_result_select
     * @param requete_sql = Requete SQL
     * @return Le résultat de la requête en paramètre, null sinon.
     */
    QList<QList<QString> > get_result_select(QString requete_sql);
    /**
     * @brief db_connection
     * @return True si la connexion est bien effectuée, false sinon
     */
    bool db_open_connection(QString &name, QString &password);
    /**
     * @brief db_close_connection
     * @return True si la connexion est bien fermée, false sinon
     */
    void db_close_connection();

private :
    QSqlDatabase db;
};

#endif // DATABASE_H
