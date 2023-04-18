#include "evenement.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QDate>
#include <QSqlQueryModel>
#include <QObject>
#include <QMessageBox>
#include <QCoreApplication>
#include <QSqlDatabase>
#include "mainwindow.h"
#include "ui_mainwindow.h"

Evenement::Evenement()
{
ref=0;     nb_p=0;       budget=0;           lieu=" ";

}

Evenement::Evenement(int ref  ,int nb_p, QDate dd , QDate df,QString lieu ,float budget){
  this->ref=ref;
    this->nb_p=nb_p;
    this->lieu=lieu;
    this->dd=dd;
    this->df=df;
    this->budget=budget;


}
int Evenement::getref(){return ref;}
int Evenement::getnb_p(){return nb_p;}
QDate Evenement::getdd(){return dd;}
QDate Evenement::getdf(){return df;}
QString Evenement::getlieu(){return lieu;}
float Evenement::getbudget(){return budget;}
void Evenement::setref(int ref){this->ref=ref;}
void Evenement::setnb_p(int nb_p){this->nb_p=nb_p;}
void Evenement::setdd(QDate dd){this->dd=dd;}
void Evenement::setdf(QDate df){this->df=df;}
void Evenement::setlieu(QString lieu){this->lieu=lieu;}
void Evenement::setbudget(float budget){this->budget=budget;}
bool Evenement::ajouter_event(){

                          QSqlQuery query;
                                                QString ref_string=QString::number(ref);
                                                QString nb_p_string=QString::number(nb_p);
                                              //  QString dd_string=QDate::fromString(dd_string,"d'MM'MMcaryyyy");
                                                  QString budget_string=QString::number(budget);
                               query.prepare("INSERT INTO EVENEMENT (ref, nb_p, dd,df,lieu,budget) "
                                             "VALUES (:ref, :nb_p, :dd, :df, :lieu, :budget)");
                               query.bindValue(":ref", ref_string);
                               query.bindValue(":nb_p", nb_p_string);
                               query.bindValue(":dd", dd);
                               query.bindValue(":df", df);
                               query.bindValue(":lieu", lieu);
                               query.bindValue(":budget", budget_string);

                              return query.exec();






                               }
bool Evenement::modifier_event(){


                          QSqlQuery query;
                                                              QString ref_string=QString::number(ref);
                                                              QString nb_p_string=QString::number(nb_p);
                                                             QString budget_string=QString::number(budget);
             query.prepare ("UPDATE EVENEMENT set ref=:ref, nb_p=:nb_p, dd=:dd,df=:df,lieu=:lieu,budget=:budget where ref = :ref") ;



                  query.bindValue(":ref", ref_string);
                  query.bindValue(":nb_p", nb_p_string);
                  query.bindValue(":dd", dd);
                  query.bindValue(":df", df);
                  query.bindValue(":lieu", lieu);
                  query.bindValue(":budget", budget_string);
                        return query.exec();





                               }

bool Evenement::supprimer_event(int ref)
{ QSqlQuery query;

query.prepare ("Delete from EVENEMENT where ref = :ref");
query. bindValue (0, ref);

return query.exec();
}

QSqlQueryModel* Evenement::afficher_event(){

    QSqlQueryModel* model=new QSqlQueryModel();


          model->setQuery("SELECT*  FROM EVENEMENT");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Reference"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nombre de Participants"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date de début"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de fin"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("Le Lieu"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("Le Budget"));





    return model;




}



QSqlQueryModel * Evenement::trie_ref()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EVENEMENT order by ref");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("REF"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("NB_P"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("DD"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("DF"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("LIEU"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("BUDGET"));

    return model;
}

QSqlQueryModel * Evenement::trie_lieu()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EVENEMENT order by lieu");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("REF"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("NB_P"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("DD"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("DF"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("LIEU"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("BUDGET"));
    return model;
}

QSqlQueryModel * Evenement::trie_nb_p()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EVENEMENT order by nb_p");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("REF"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("NB_P"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("DD"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("DF"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("LIEU"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("BUDGET"));
    return model;
}
bool Evenement ::existeId(int ref)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM EVENEMENT WHERE ref = :ref");
    query.bindValue(":ref", ref);
    if (query.exec() && query.next()) {
        return true; // L'ID existe dans bd
    }
    return false; // L'ID n'existe pas dans bd
}
