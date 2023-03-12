#ifndef RECHERCHE_H
#define RECHERCHE_H
#include <QString>
#include <QDate>

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

private:
   int NUM_R;
   QString NOM;
   QString TYPE;
   QDate DATE_DEBUT;
   QDate DATE_FIN;
   int PRIX;

};

#endif // RECHERCHE_H
