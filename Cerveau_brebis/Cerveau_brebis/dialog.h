#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLayout>
#include <QLabel>
#include <QDebug>
/**
 * @brief Cette classe crée une boîte de dialogue.
 * La boîte de dialogue permet à l'utilisateur de saisir les identifiants
 * de la base de données.
 */
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog(){}
signals:
    /**
     * @brief Emet un signal avec les informations saisies par l'utilisateur
     * @param user Nom de l'utilisateur de la base de données
     * @param password Mot de passe de la base de données
     */
    void info(QString user, QString password);

private slots:
    /**
     * @brief Action lorsque le button ok est cliqué
     */
    void okButtonPushed();
    /**
     * @brief Ferme la fenêtre lorsque le bouton cancel est cliqué.
     */
    void cancelButtonPushed();
private:

    QPushButton* okButton;
    QPushButton* cancelButton;
    QLineEdit* userText;
    QLineEdit* passwordText;
    QLabel* userLabel;
    QLabel* passwordLabel;

};

#endif // DIALOG_H
