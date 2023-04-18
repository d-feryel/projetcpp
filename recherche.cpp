#include "recherche.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QString>
#include <QDate>
#include <QObject>




Recherche::Recherche()
{

}
Recherche::Recherche(int NUM_R,QString NOM,QString TYPE,QDate DATE_DEBUT,QDate DATE_FIN,int PRIX)
{
    this->NUM_R=NUM_R;
    this->NOM=NOM;
    this->TYPE=TYPE;
    this->DATE_DEBUT=DATE_DEBUT;
    this->DATE_FIN=DATE_FIN;
    this->PRIX=PRIX;
}

int Recherche::getNUM_R(){return NUM_R;}
QString Recherche::getNOM(){return NOM;}
QString Recherche::getTYPE(){return TYPE;}
QDate Recherche::getDATE_DEBUT(){return DATE_DEBUT;}
QDate Recherche::getDATE_FIN(){return DATE_FIN;}
int Recherche::getPRIX(){return PRIX;}

void Recherche::setNUM_R(int NUM_R){this->NUM_R=NUM_R;}
void Recherche::setNOM(QString NOM){this->NOM=NOM;}
void Recherche::setTYPE(QString TYPE){this->TYPE=TYPE;}
void Recherche::setDATE_DEBUT(QDate DATE_DEBUT){this->DATE_DEBUT=DATE_DEBUT;}
void Recherche::setDATE_FIN(QDate DATE_FIN){ this->DATE_FIN=DATE_FIN;}
void Recherche::setPRIX(int PRIX){this->PRIX=PRIX;}
bool Recherche::ajouterRecherche()
{
    bool test=false;
    QSqlQuery query;
    QString NUM_R_string= QString::number(NUM_R);
    QString PRIX_string= QString::number(PRIX);

         query.prepare("INSERT INTO RECHERCHE (NUM_R, NOM, TYPE,DATE_DEBUT,DATE_FIN,PRIX) "
                       "VALUES (:NUM_R, :NOM, :TYPE,:DATE_DEBUT,:DATE_FIN,:PRIX)");
         query.bindValue(":NUM_R", NUM_R_string);
         query.bindValue(":NOM", NOM);
         query.bindValue(":TYPE", TYPE);
         query.bindValue(":DATE_DEBUT", DATE_DEBUT);
         query.bindValue(":DATE_FIN", DATE_FIN);
         query.bindValue(":PRIX", PRIX_string);

         query.exec();
  return test ;
}
bool Recherche::suppRecherche(int NUM_R)
{
    QSqlQuery query;

         query.prepare("delete from RECHERCHE where NUM_R=:NUM_R");
         query.bindValue(0, NUM_R);

         query.exec();


}


QSqlQueryModel* Recherche::afficherRecherche()
{
    QSqlQueryModel *model=new QSqlQueryModel();

        model->setQuery("SELECT * FROM RECHERCHE");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Numero"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de debut"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de fin"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Prix"));


    return model;


}



bool Recherche::modifierRecherche()
{
    QSqlQuery query;
    QString NUM_R_string= QString::number(NUM_R);
    QString PRIX_string= QString::number(PRIX);

         query.prepare("UPDATE RECHERCHE set NUM_R=:NUM_R, NOM=:NOM, TYPE=:TYPE,DATE_DEBUT=:DATE_DEBUT,DATE_FIN=:DATE_FIN,PRIX=:PRIX where NUM_R=:NUM_R") ;
         query.bindValue(":NUM_R", NUM_R_string);
         query.bindValue(":NOM", NOM);
         query.bindValue(":TYPE", TYPE);
         query.bindValue(":DATE_DEBUT", DATE_DEBUT);
         query.bindValue(":DATE_FIN", DATE_FIN);
         query.bindValue(":PRIX", PRIX_string);
return  query.exec();

}

QSqlQueryModel * Recherche::AfficherTrieNum()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM RECHERCHE ORDER BY NUM_R");
    return model;
}


QSqlQueryModel * Recherche::AfficherTriePrix()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM RECHERCHE ORDER BY PRIX");
    return model;
}

QSqlQueryModel * Recherche::AfficherTrieDate_fin()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM RECHERCHE ORDER BY DATE_FIN");
    return model;
}

QSqlQueryModel * Recherche::rechercherNUM_R(QString NUM_R)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select * from RECHERCHE where NUM_R like ?");
    q.addBindValue("%"+ NUM_R +"%");
    q.exec();
    model->setQuery(q);
    return (model);
}

QSqlQueryModel * Recherche::rechercherPRIX(QString PRIX)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select * from RECHERCHE where PRIX like ?");
    q.addBindValue("%"+ PRIX +"%");
    q.exec();
    model->setQuery(q);
    return (model);
}











