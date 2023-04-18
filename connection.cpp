#include "connection.h"
#include <QDebug>
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("yefa");//inserer nom de l'utilisateur
db.setPassword("yefa");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

qDebug()<< "connection : " << test;




    return  test;
}
void Connection::closeConnection(){db.close();}
