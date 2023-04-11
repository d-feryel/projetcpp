
#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class Employe
{
    QString nom,prenom,adresse,poste;
    int CIN,numero;
public:
    Employe();
    Employe(int,QString,QString,QString,int,QString);
    QString getNom(){
        return nom;
    }
    QString getPrenom(){
        return prenom;
    }
    QString getAdresse(){
        return adresse ;
    }
    QString getPoste(){
        return poste;
    }
    int getnumero(){
        return numero;
    }
    int getCIN(){
        return CIN;
    }
    void setNom(QString nom){
        this->nom = nom;
    }
    void setPrenom(QString prenom){
        this->prenom = prenom;
    }
    void setAdresse(QString adresse){
        this->adresse = adresse;
    }

    void setPoste(QString poste){
        this->poste = poste;
    }
    void setCIN(int CIN){
        this->CIN = CIN;
    }
    void setnumero(int numero){
        this->numero = numero;
    }
    bool ajouter();
    bool supprimer(int CIN);
    QSqlQueryModel * afficher();
     bool modifier(int CIN);
     QSqlQueryModel * show_Desc_name();
     QSqlQueryModel * show_Asc_name();

     QSqlQueryModel * chercher(QString cher);
      QSqlQueryModel * tri_num();
};


#endif // EMPLOYE_H
