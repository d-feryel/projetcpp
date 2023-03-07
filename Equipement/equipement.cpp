#include "equipement.h"

Equipement::Equipement(int NSERIE,QString NREF,QString QANT,QString NOMQ,QString DESCRP)
{
    this->NOMQ=NOMQ;
    this->NSERIE=NSERIE;
    this->NREF=NREF;
    this->QANT=QANT;
    this ->DESCRP=DESCRP;
}
bool Equipement::ajouterequipement()
{

}
QSqlQueryModel * afficherequipement()
{

}
bool Equipement::supprimerequipement(int NSERIE)
{

}
