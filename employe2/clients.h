#ifndef CLIENTS_H
#define CLIENTS_H
#include <QString>
#include <QSqlQueryModel>

class Clients
{
public:
    Clients();
    Clients(int,QString,QString,int,QString ) ;
      int getcin2();
     void setcin2(int);

     QString getNOM();
     void setNOM(QString);


     QString getPRENOM();
     void setPRENOM(QString);

     int getNUM() ;
     void setNUM(int);


     QString getAdresse();
     void setAdresse(QString);

     bool ajouter();
     QSqlQueryModel* afficher();
     bool supprimer (int) ;
     bool modifier(int,QString,QString,int,QString) ;

     QSqlQueryModel * AfficherTrieNum();
     QSqlQueryModel * AfficherTriecin();
     QSqlQueryModel * AfficherTrieNom();

     QSqlQueryModel * rechercherNUM(QString);

     private :
     int cin2;
     QString nom;
     QString prenom;
     int num;
     QString adresse;



};

#endif // CLIENTS_H
