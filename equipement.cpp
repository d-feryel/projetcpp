#include "equipement.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include <QSqlQueryModel>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QSqlQuery>
#include <iostream>
#include <QTextStream>
#define STR_EQUAL 0
#include <cstdlib>
using namespace std;
Ui_MainWindow ui;

equipement::equipement()
{
     nref=0;
     dateq= QDate(2000, 7,1);
     nomeq="";
    qant=0;
    descr= "";
    prix = 0;
}

equipement::equipement(int nref,QDate dateq,QString nomeq,int qant,QString descr,int prix)
{
    this->nref=nref;
    this->dateq=dateq;
    this->nomeq=nomeq;
    this->qant=qant;
    this->descr=descr;
    this->prix=prix;


}
int equipement:: getnref()
{
    return nref;

}
QDate equipement::getdate()
{
return dateq;
}
QString equipement::getnomeq()
{
return nomeq;
}
int equipement::getqant()
{
    return qant;
}
 QString equipement::getdesc()
 {
     return descr;
 }
 int equipement::getprix()
 {
     return prix;
 }
 void equipement::setnref(int nref)
 {
     this->nref=nref;
 }
 void equipement::setdate(QDate dateq)
 {
     this->dateq=dateq;
 }
 void equipement::setnomeq(QString nomeq)
 {
     this->nomeq=nomeq;
 }
 void equipement::setqant(int qant)
 {
     this->qant=qant;
 }
 void equipement::setdescr(QString descr)
 {
     this->descr=descr;
 }
 void equipement::setprix(int prix)
 {
     this->prix=prix;
 }
 bool equipement::ajouter()
 {

     QSqlQuery query;
     QString prix_string=QString::number(prix);
     QString qant_string=QString::number(qant);
     QString nref_string=QString::number(nref);




     query.prepare("INSERT INTO EQUIPEMENT (NREF,DAT,NOMEQ,QANT,DESCRP,PRIX) "
                         "VALUES (:NREF,:DAT,:NOMEQ,:QANT,:DESCRP,:PRIX)");

     query.bindValue(":NREF", nref_string);
     query.bindValue(":DAT", dateq);
     query.bindValue(":NOMEQ", nomeq);
     query.bindValue(":QANT", qant_string);
     query.bindValue(":DESCRP", descr);
     query.bindValue(":PRIX", prix_string);


     return    query.exec();
 }

 bool equipement::supprimer(int nref)
      {
     QString n=QString::number(nref);
      QSqlQuery query;
      query.prepare("DELETE FROM EQUIPEMENT WHERE NREF=:nref");

      query.bindValue(":nref", n);



           return query.exec();
  }

 QSqlQueryModel* equipement::afficher(){

      QSqlQueryModel* model=new QSqlQueryModel();
            model->setQuery("SELECT* FROM EQUIPEMENT");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("NREF"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("DAT"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOMEQ"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("QANT"));
           model->setHeaderData(4, Qt::Horizontal, QObject::tr("DESCRP"));
           model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRIX"));

            return model;
 }




 bool equipement::modifier()
 {
     QSqlQuery query;
     QString prix_string=QString::number(prix);
     QString qant_string=QString::number(qant);
     QString nref_string=QString::number(nref);




           query.prepare("UPDATE EQUIPEMENT SET NREF=:nref, DAT=:dateq , NOMEQ=:nomeq, QANT=:qant ,DESCRP=:descr , PRIX=:prix WHERE NREF=:nref");

           query.bindValue(":nref", nref_string);
           query.bindValue(":dateq", dateq);
           query.bindValue(":nomeq", nomeq);
           query.bindValue(":qant",qant_string );
           query.bindValue(":descr", descr);
           query.bindValue(":prix", prix_string);


          return query.exec();
 }

 QSqlQueryModel* equipement::trier_ref()
 {
     QSqlQuery *q = new QSqlQuery();
     QSqlQueryModel *model = new QSqlQueryModel();
     q->prepare("SELECT * FROM  EQUIPEMENT ORDER BY NREF ASC ");
     q->exec();
     model->setQuery(*q);
     return model;
 }

 QSqlQueryModel* equipement::trier_prix()
 {
     QSqlQuery *q = new QSqlQuery();
     QSqlQueryModel *model = new QSqlQueryModel();
     q->prepare("SELECT * FROM  EQUIPEMENT ORDER BY PRIX ASC ");
     q->exec();
     model->setQuery(*q);
     return model;
 }
 QSqlQueryModel* equipement::trier_qant()
 {
     QSqlQuery *q = new QSqlQuery();
     QSqlQueryModel *model = new QSqlQueryModel();
     q->prepare("SELECT * FROM  EQUIPEMENT ORDER BY QANT ASC ");
     q->exec();
     model->setQuery(*q);
     return model;
 }
/*
 QSqlQueryModel * equipement ::recherche(QString res)
      {


          QSqlQueryModel *model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM EQUIPEMENT WHERE ( NREF LIKE '%"+res+"%' OR DAT LIKE '%"+res+"%' OR NOMEQ LIKE '%"+res+"%' OR QANT '%"+res+"%' OR DESCRP LIKE '%"+res+"%' OR PRIX '%"+res+"%'   ) ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("NREF"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("DAT"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOMEQ"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("QANT"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("DESCRP"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRIX"));


          return model;
      }

*/
 void equipement::creation_pdf()
 {
     QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
       if (QFileInfo(fileName).suffix().isEmpty())
           { fileName.append(".pdf"); }

       QPrinter printer(QPrinter::PrinterResolution);
       printer.setOutputFormat(QPrinter::PdfFormat);
       printer.setPaperSize(QPrinter::A4);
       printer.setOutputFileName(fileName);

       QTextDocument doc;
       QSqlQuery q;
       q.prepare("SELECT * FROM EQUIPEMENT ");
       q.exec();
       QString pdf="<br> <h1  style='color:blue'>LISTE DES EQUIPEMENT  <br></h1>\n <br> <table>  <tr>  <th>NREF  </th> <th>DAT  </th> <th>NOMEQ  </th><th>QANT  </th><th> DESCRP </th><th>PRIX </th> </tr>" ;
   //br traja ll star oel tr tzidlek colonne th tzidlek ligne h1 asghrr size o akbr size h6 //

       while ( q.next())
           {

           pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+" " + q.value(1).toString() +"</td>   <td>" +q.value(2).toString() +" <td>" +q.value(3).toString() +" <td>" +q.value(4).toString() +" <td>" +q.value(5).toString() +"  <td>"  +q.value(6).toString() +" <td>" +q.value(7).toString() +" <td>" +q.value(8).toString() +"  "" " "</td> </td>" ;
       }
       doc.setHtml(pdf);
       doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
       doc.print(&printer);
 }


 QSqlQueryModel * equipement::chercher(QString cher)
      {
          QSqlQueryModel * model= new QSqlQueryModel();

       model->setQuery("select * from EQUIPEMENT where upper(NREF) LIKE upper('%"+cher+"%')");


      return model;
      }

bool equipement::ajouter_historique(QString nom,int nref,QString nomeq)
 {
     QSqlQuery query;
     QString ref=QString ::number(nref);


     query.prepare("INSERT INTO history (nom, date_historique, nref, nomeq) "
                   "VALUES (:nom, :date_historique, :nref, :nomeq)");
     query.bindValue(":nom",nom);
     query.bindValue(":date_historique", QDateTime::currentDateTime());
     query.bindValue(":nref", ref);
     query.bindValue(":nomeq", nomeq);

     return    query.exec();




 }

 QSqlQueryModel * equipement::afficher_historique0()
 {
     QSqlQueryModel * model= new QSqlQueryModel();


         model->setQuery("select * FROM history");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("Description "));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("date d'historique"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("reference"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("nom d'equipement"));


     return model;

     }

 QSqlQueryModel * equipement::afficher_historique(QString type)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
      QString a;
      if(type=="tout")
      {        model->setQuery("select * FROM history");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Description "));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("date d'historique"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("reference"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("nom d'equipement"));
      }
      else{
         model->setQuery("select * FROM history  WHERE nom LIKE '%"+type+"%'  ");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("Description "));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("date d'historique"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("reference"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("nom d'equipement"));
 }
     return model;
 }
 bool equipement::supprimerh(int id)
 {

     QSqlQuery query;

          query.prepare("DELETE from history where nref=:nref ");
          query.bindValue(":nref", id);
      return     query.exec();

 }
