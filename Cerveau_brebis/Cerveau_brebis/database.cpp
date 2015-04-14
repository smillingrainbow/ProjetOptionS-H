#include "database.h"
using namespace std;

bool Database::db_open_connection(QString& name, QString& password, bool newLogin)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");

//    qDebug() << "Database " ;
//    qDebug()<< "Name : " << name ;
//    qDebug() << "Password : " << password;

    // si les identifiants ont été modifiés
    if(newLogin){
        db.setUserName(name);
        db.setPassword(password);
    } // sinon identifiants par défaut
    else{
        db.setUserName("root");
        db.setPassword("root");
    }

    db.setDatabaseName("structurecerveaubrebis");

    if(db.open())
    {
//        cout << "Connexion à la base de données effectuée." << endl;
        return true;
    }
    else
    {
//        QMessageBox msgBox;
//        msgBox.setText("La connexion à la base de données a échouée");
//        msgBox.exec();
        cout << "La connexion à la base de données a échoué." << endl;
        return false;
    }
}

void Database::db_close_connection()
{
    db.close();
//    cout << "Fermeture de la base de données." << endl;

}

QList<QList<QString> > Database::get_result_select(QString requete_sql)
{
    QList<QList<QString> > result;
    QSqlQuery query;

    if(query.exec(requete_sql)){
        int nb_column = query.record().count();
//        int nb_ligne = query.size();
//        cout << "Nombre  de colonne : " << nb_column << endl;
        while(query.next()){
            QList<QString> list;
            for(int colonne=0; colonne < nb_column; colonne++){
                list.append(query.value(colonne).toString());
            }
            result.append(list);
        }
//        cout << "Fin de la récupération du résultat de la requête." << endl;
    }else{ // Erreur
//        QMessageBox msgBox;
//        msgBox.setText("Erreur lors de l'exécution de la requête.");
//        msgBox.exec();
        cout << "Erreur lors de l'exécution de la requête." << endl;
        qDebug() << query.lastError();
    }

    return result;
}
