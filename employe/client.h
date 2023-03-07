#ifndef CLIENT_H
#define CLIENT_H
#include <QString>

class Client
{
public:
    Client();
    Client(int,int,QString,QString,QString);
    int getCIN2();
    int getnuméro();
    QString getnom();
    QString getprénom();
    QString getadresse();
    void setCIN2(int);
    void setnuméro(int);
    void setnom(QString);
    void setprénom(QString);
    void setadresse(QString);

   bool ajouter();

private :
    int CIN2,numéro;
    QString nom,prénom,adresse;



};

#endif // CLIENT_H
