#ifndef EVENEMENT_H
#define EVENEMENT_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
namespace Ui {
class Evenement;
}
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
    bool ajouter_event();
    bool modifier_event();
    bool supprimer_event(int ref);
    QSqlQueryModel* afficher_event();
    void chercher_event(const QString &le_chercher);
    QSqlQueryModel * trie_ref();
    QSqlQueryModel * trie_lieu();
    QSqlQueryModel * trie_nb_p();
    bool existeId(int ref);



private :
    Ui::Evenement *ui;
    int ref,nb_p;
    QString lieu;
    float budget;
    QDate dd,df;

};

#endif // EVENEMENT_H
