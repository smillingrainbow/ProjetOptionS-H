#include "database.h"
using namespace std;

bool Database::db_open_connection()
{
    db = QSqlDatabase::addDatabase("QSQLITE","");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName("structurecerveaubrebis.sqli");

    if(db.open())
    {
        cout << "Connexion à la base de données effectuée." << endl;
        return true;
    }
    else
    {
        cout << "La connexion à la base de données a échoué." << endl;
        return false;
    }
}

void Database::db_close_connection()
{
    db.close();
    cout << "Fermeture de la base de données." << endl;

}

QList<QList<QString> > Database::get_result_select(QString requete_sql)
{
    QList<QList<QString> > result;
    QSqlQuery query;

    if(query.exec(requete_sql)){
        int nb_column = query.record().count();
        while(query.next())
        {
            int count=0;
            for(int i=0; i<nb_column;i++) // TODO : VERIFIER QUE L'INDICE COMMENCE A 0
                result[count][i] = query.value(i).toString(); // remplissage de la liste avec le résultat de la requête
            count++;
        }
        cout << "Fin de la récupération du résultat de la requête." << endl;
    }else{ // Erreur
        cout << "Erreur lors de l'exécution de la requête." << endl;
        qDebug() << query.lastError();
    }

    return result;
}






