#include "evenement.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QDate>
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
bool Evenement::ajouter(){bool test=false;

                          QSqlQuery query;
                                                QString ref_string=QString::number(ref);
                                                QString nb_p_string=QString::number(nb_p);
                                              //  QString dd_string=QDate::fromString(dd_string,"d'MM'MMcaryyyy");
                                                  QString budget_string=QString::number(budget);
                               query.prepare("INSERT INTO Evenement (ref, nb_p, dd,df,lieu,budget) "
                                             "VALUES (:ref, :nb_p, :dd, :df, :lieu, :budget)");
                               query.bindValue(":ref", ref_string);
                               query.bindValue(":nb_p", nb_p_string);
                               query.bindValue(":dd", dd);
                               query.bindValue(":df", df);
                               query.bindValue(":lieu", lieu);
                               query.bindValue(":budget", budget);

                               query.exec();





              return test;}
