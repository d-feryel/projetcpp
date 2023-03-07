#ifndef EVENEMENT_H
#define EVENEMENT_H
#include <QString>
#include <QDate>
class Evenement
{
public:
    Evenement();
    Evenement(int ,int ,QDate ,QDate ,QString ,float);
    int getref();
    int getnb_p();
    QDate getdd();
    QDate getdf();
    QString getlieu();
    float getbudget();
    void setref(int);
    void setnb_p(int);
    void setdd(QDate);
    void setdf(QDate);
    void setlieu(QString);
    void setbudget(float);
    bool ajouter();





private :
    int ref,nb_p;
    QString lieu;
    float budget;
    QDate dd,df;

};

#endif // EVENEMENT_H
