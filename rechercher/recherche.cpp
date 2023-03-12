#include "recherche.h"

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
void Recherche::setPRIX(int PRIX){this->PRIX=PRIX; }
