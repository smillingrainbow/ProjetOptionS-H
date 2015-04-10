#include "dialog.h"

using namespace std;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout* vbox = new QVBoxLayout();
    QHBoxLayout* hboxUser = new QHBoxLayout();
    QHBoxLayout* hboxPassword = new QHBoxLayout();
    QHBoxLayout* hboxButton = new QHBoxLayout();

    okButton = new QPushButton("Ok");
    cancelButton = new QPushButton("Annuler");
    userText = new QLineEdit();
    userLabel = new QLabel();
    userLabel->setText("Nom utilisateur");
    passwordText = new QLineEdit();
    passwordLabel = new QLabel();
    passwordLabel->setText("Mot de passe");

    hboxUser->addWidget(userLabel);
    hboxUser->addWidget(userText);

    hboxPassword->addWidget(passwordLabel);
    hboxPassword->addWidget(passwordText);

    hboxButton->addWidget(okButton);
    hboxButton->addWidget(cancelButton);

    vbox->addLayout(hboxUser);
    vbox->addLayout(hboxPassword);
    vbox->addLayout(hboxButton);

    this->setLayout(vbox);
    this->setWindowTitle("Identification");

    connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonPushed()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonPushed()));

}

void Dialog::okButtonPushed()
{
    qDebug() << "Dialog ";
    qDebug()<< "Name : " << userText->text();
    qDebug() << "Password : " << passwordText->text();
    emit info(userText->text(), passwordText->text());
    this->close();
}

void Dialog::cancelButtonPushed()
{
    this->close();
}
