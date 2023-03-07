#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Equipement
{ int NSERIE;
    QString NREF,NOMQ,QANT,DESCRP;
public:
        //constructeurs
    Equipement();
      Equipement(int NSERIE,QString NREF,QString QANT,QString NOMQ,QString DESCRP);
      //Getters

      QString getNom()
      {
          return NOMQ;
      }
      int getNserie()
      {
          return NSERIE;
      }
      QString getQant()
      {
          return QANT;
      }
      QString getDescrp()
      {
          return DESCRP;
      }

      //Setters

       int setNserie(int ns)
       {
           NSERIE= ns;
       }
       void setNom(QString n)
       {
           NOMQ=n;
       }
       void setNref(QString nf)
       {
           NREF=nf;
       }
       void setQant(QString qt)
       {
           QANT=qt;
       }
       void setDesc(QString des)
       {
           DESCRP=des;
       }
       //Fonctionnalités de Base relatives à l'entité equipement
       bool ajouterequipement();
       QSqlQueryModel * afficherequipement();
       bool supprimerequipement(int NSERIE);
};

#endif // EQUIPEMENT_H
