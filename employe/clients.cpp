#include "clients.h"

#include <QString>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QMessageBox>


Clients::Clients()
{
     cin2 = 0;
     nom = " " ;
     prenom = " ";
     num= 0  ;
     adresse = " " ;

}
Clients::Clients(int cin2 ,QString nom ,QString prenom,int num ,QString adresse)
{
    this->cin2 = cin2 ;
     this->nom = nom ;
    this->prenom = prenom ;
     this->num = num ;
     this->adresse = adresse ;



}
int Clients::getcin2()
{return cin2; }
void Clients::setcin2(int cin2 )
{ this->cin2 = cin2 ;}



QString Clients::getNOM()
{return nom ; }
void Clients::setNOM(QString nom)
{this->nom = nom ;}



QString Clients::getPRENOM()
{return prenom ; }
void Clients::setPRENOM(QString prenom)
{this->prenom = prenom ;}

int Clients::getNUM()
{return num; }
void Clients::setNUM (int num)
{ this->num = num ;}

QString  Clients::getAdresse()
{return adresse ; }
void  Clients::setAdresse(QString adresse)
{this->adresse = adresse ;}








bool Clients::ajouter()
{
 QSqlQuery query;

 QString cin_string=QString::number(cin2);
 QString num_string=QString::number(num);


       query.prepare("INSERT INTO CLIENTS (cin2,nom,prenom,num,adresse) "
                     "VALUES (:cin2, :nom,:prenom, :num, :adresse)");
       query.bindValue(":cin2", cin_string);
       query.bindValue(":nom", nom);
       query.bindValue(":prenom", prenom);
       query.bindValue(":num", num_string);
       query.bindValue(":adresse",adresse);

       return query.exec();



}
bool Clients::supprimer(int cin2)
{
    QSqlQuery query;
    QString cin_string=QString::number(cin2);

          query.prepare(" Delete from Clients where cin2=:cin2");
          query.bindValue(0, cin_string);



    return query.exec();
}

bool Clients::modifier(int cin2 ,QString nom ,QString prenom,int num ,QString adresse)
{
    QSqlQuery query;
    QString cin_string=QString::number(cin2);
    QString num_string=QString::number(num);

          query.prepare("update Clients set cin2=:cin2,nom=:nom,prenom=:prenom,num=:num,adresse=:adresse where cin2=:cin2");
          query.bindValue(":cin2", cin_string);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":num", num_string);
          query.bindValue(":adresse",adresse);


  return query.exec();
}
QSqlQueryModel* Clients::afficher()
{
 QSqlQueryModel* model=new QSqlQueryModel();

       model->setQuery("SELECT* FROM Clients");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
       model->setHeaderData(7, Qt::Horizontal, QObject::tr("numero"));
       model->setHeaderData(8, Qt::Horizontal, QObject::tr("adresse"));


  return model;}
QSqlQueryModel * Clients::AfficherTrieNum()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENTS ORDER BY NUM");
    return model;
}

QSqlQueryModel * Clients::AfficherTriecin()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENTS ORDER BY Cin2");
    return model;
}


QSqlQueryModel * Clients::AfficherTrieNom()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Clients order by nom");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("SEXE"));
    return model;
}


QSqlQueryModel * Clients::rechercherNUM(QString NUM)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select * from Clients where NUM like ?");
    q.addBindValue("%"+ NUM +"%");
    q.exec();
    model->setQuery(q);
    return (model);
}

