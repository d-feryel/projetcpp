#include "client.h"
#include <QSqlQuery>
#include<QtDebug>
#include <QString>
Client::Client()
{



}
Client :: Client(int CIN2,int numéro,Qstring nom,QString prénom ,QString adresse)
{this->CIN2=CIN2;this->numéro=numéro ;this->nom=nom;this->prénom=prénom;this->adresse=adresse;}
int Client:: getCIN2(){return CIN2;}
int Client::getnuméro(){return numéro;}
QString Client:: getnom(){return nom;}
QString Client:: getprénom(){return prénom;}
QString Client::getadresse(){return adresse;}
void Client:: setCIN2(int CIN2){this->CIN2=CIN2;}
void Client:: setnuméro(int numéro){this->numéro=numéro;}
void Client:: setnom(QString nom){this->nom=nom;}
void Client:: setprénom(QString prénom){this->prénom=prénom;}
void Client:: setadresse(QString adresse){this->adresse=adresse;}
bool Client:: ajouter()
{
    bool test=false;

    QSqlQuery query;
    Qstring
         query.prepare("INSERT INTO GS_CLIENTS (CIN2, NOM, PRÉNOM,NUMÉRO,ADRESSE) "
                       "VALUES (:id, :forename, :surname, :num, :adress)");
         query.bindValue(":id", CIN2);
         query.bindValue(":forename", NOM);
         query.bindValue(":surname",PRÉNOM );
         query.bindValue(":num", );NUMÉRO
         query.bindValue(":adress",ADRESSE );
         query.exec();


    return test;



}

