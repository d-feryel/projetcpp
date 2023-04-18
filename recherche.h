#ifndef RECHERCHE_H
#define RECHERCHE_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>



class Recherche
{
public:
    Recherche();
    Recherche(int,QString,QString,QDate,QDate,int);
    int getNUM_R();
    QString getNOM();
    QString getTYPE();
    QDate getDATE_DEBUT();
    QDate getDATE_FIN();
    int getPRIX();
    void setNUM_R(int);
    void setNOM(QString);
    void setTYPE(QString);
    void setDATE_DEBUT(QDate);
    void setDATE_FIN(QDate);
    void setPRIX(int);
    bool ajouterRecherche();
   QSqlQueryModel* afficherRecherche();
   bool suppRecherche (int NUM_R);
   bool modifierRecherche();

   QSqlQueryModel * AfficherTrieNum();
   QSqlQueryModel * AfficherTriePrix();
   QSqlQueryModel * AfficherTrieDate_fin();
   QSqlQueryModel * rechercherNUM_R(QString);
   QSqlQueryModel * rechercherPRIX(QString);



private:
   int NUM_R;
   QString NOM;
   QString TYPE;
   QDate DATE_DEBUT;
   QDate DATE_FIN;
   int PRIX;

};

#endif // RECHERCHE_H
