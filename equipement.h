#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include <QSqlQuery>
#include<QString>
#include <QtDebug>
#include<QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <iostream>
#include <cstdlib>


using namespace std;

class equipement
{
public:

    equipement();

equipement(int,QDate,QString,int,QString,int);
int getnref();
 QDate getdate();
  QString getnomeq();
    int getqant();
    QString getdesc();
    int getprix();
    void setprix(int);
    void setqant(int);
    void setnref(int);
    void setnomeq(QString);
    void setdescr(QString);
    void setdate(QDate);
    //crud
    bool ajouter();
     QSqlQueryModel* afficher();
    bool supprimer(int n);
     bool modifier();
//tri
QSqlQueryModel * trier_ref();
QSqlQueryModel * trier_prix();
QSqlQueryModel * trier_qant();
//recherche
 QSqlQueryModel * chercher(QString cher);
 //pdf
  void creation_pdf();
  //histoqiue
 QSqlQueryModel * afficher_historique0();
  QSqlQueryModel * afficher_historique(QString type);
bool ajouter_historique(QString nomeq,int nref,QString descr);
 bool supprimerh(int id);

private :
    int prix,qant,nref;
    QString nomeq,descr;
    QDate dateq;
};

#endif // EQUIPEMENT_H
