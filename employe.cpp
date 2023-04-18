#include "employe.h"
#include <QDebug>


Employe:: Employe(){
   /* CIN = 0;
    nom = "";
    prenom = "";
    adresse = "";
    numero = 0;
    poste = "";*/
}
Employe::Employe(int CIN , QString nom, QString prenom, QString adresse , int numero, QString poste)
{
this->CIN = CIN;
this->nom = nom;
this->prenom = prenom;
 this->adresse = adresse;
 this->numero = numero ;
 this->poste = poste;
}
bool Employe :: ajouter(){
    QSqlQuery query;
    QString res =  QString :: number(CIN);
    query.prepare("insert into employe (CIN,nom,prenom,adresse,numero,poste)" "values (:CIN,:nom,:prenom,:adresse,:numero,:poste)");
    query.bindValue(":CIN",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":adresse",adresse);
     query.bindValue(":numero",numero);
     query.bindValue(":poste",poste);
     return query.exec();
}

bool Employe :: supprimer(int CIN){
    QSqlQuery query;
           QString res = QString::number(CIN);
           query.prepare("Delete from employe where CIN= :CIN");
        query.bindValue(":CIN",res);

           return query.exec();
}
QSqlQueryModel * Employe :: afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from employe");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE_MAIL"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Numero"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("POSTE"));

    return model;
}
 bool Employe :: modifier(int CIN)
 {
     QSqlQuery query;
         query.prepare("update employe set CIN=:CIN,nom=:nom,prenom=:prenom,adresse=:adresse,numero=:numero,poste=:poste where CIN= :CIN");


         query.bindValue(":CIN",CIN);
         query.bindValue(":nom",nom);
         query.bindValue(":prenom",prenom);
         query.bindValue(":adresse",adresse);
          query.bindValue(":numero",numero);
          query.bindValue(":poste",poste);

         return query.exec();


 }
 QSqlQueryModel * Employe::show_Desc_name()
 {
     QSqlQueryModel* model = new QSqlQueryModel();
      model->setQuery("select * from employe ORDER BY nom ASC ");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("numero"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("poste"));
      return model;
 }
 QSqlQueryModel * Employe::show_Asc_name()
 {
     QSqlQueryModel* model = new QSqlQueryModel();
      model->setQuery("select * from employe ORDER BY CIN ASC ");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("numero"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("poste"));
      return model;
 }

 QSqlQueryModel * Employe::chercher(QString cher)
     {
         QSqlQueryModel * model= new QSqlQueryModel();

      model->setQuery("select * from employe where upper(CIN) LIKE upper('%"+cher+"%')");
     return model;
     }


 QSqlQueryModel * Employe::tri_num()
 {
     QSqlQueryModel* model = new QSqlQueryModel();
      model->setQuery("select * from employe ORDER BY numero ASC ");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("numero"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("poste"));
      return model;
 }



