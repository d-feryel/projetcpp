#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QDebug>
#include <QMessageBox>
#include <QIntValidator>
#include "ui_stat_combo.h"
#include "stat_combo.h"
#include "chat.h"
#include "ui_chat.h"
//IMPO CHAT
#include <QPlainTextEdit>
#include <QPrinter>
//#include <QPrinterInfo>
//#include <QPrintDialog>
#include <QTextStream>
#include <QPainter>
#include <QTextStream>
#include <QFileDialog>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <strstream>
#include <QSystemTrayIcon>
#include <QRegExpValidator>
#include <QDesktopServices>
#include <QUrl>
#include <QGuiApplication>
//#include <QQmlApplicationEngine>
#include <QTcpSocket>
//#include <QQuickItem>
#include <QSystemTrayIcon>
#include <QIntValidator>
#include <QPixmap>
#include <QDesktopServices>
#include <QImage>
#include <QSystemTrayIcon>
//pdf imports
#include <QModelIndex>
#include <QPdfWriter>
#include <QPainter>
#include <QUrl>
#include <QDesktopServices>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtNetwork>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   ui->lineEdit->setValidator(new QIntValidator(1,9999999,this));
    ui->lineEdit_5->setValidator(new QIntValidator(0,9999999,this));

    QString styleSheet = "QWidget#tab { background-image: url(C:/Users/ALYSSA/Desktop/takwa.png);  background-repeat: no-repeat;  background-size:100% 100%; }";
      ui->tab->setStyleSheet(styleSheet);
      ui->tableView->setModel(Etmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    int CIN = ui->lineEdit->text().toInt();
       QString nom = ui->lineEdit_2->text();
       QString prenom = ui->lineEdit_3->text();
       QString adresse = ui->lineEdit_4->text();
       int numero = ui->lineEdit_5->text().toInt();
       QString poste = ui->lineEdit_6->text();
       Employe E(CIN,nom,prenom,adresse,numero,poste);

       if ( nom.contains(QRegExp("[^a-zA-Z]"))||nom.isEmpty() ) {
               QMessageBox::warning(this, "Erreur de saisie", "Veuillez entrer un nom valide");
                ui->lineEdit_2->clear();
           }
       if ( prenom.contains(QRegExp("[^a-zA-Z]"))||prenom.isEmpty() ) {
               QMessageBox::warning(this, "Erreur de saisie", "Veuillez entrer un prenom valide");
                ui->lineEdit_3->clear();
           }
       QRegularExpression regex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");

          if (!regex.match(adresse).hasMatch()) {
              QMessageBox::warning(this, "Erreur de saisie", "Veuillez entrer une adresse e-mail valide");
             ui->lineEdit_4->clear();
          }
          if ( poste.contains(QRegExp("[^a-zA-Z]"))||poste.isEmpty() ) {
                  QMessageBox::warning(this, "Erreur de saisie", "Veuillez entrer un poste valide");
                   ui->lineEdit_6->clear();
              }



       bool test = E.ajouter();
       if (test)
       {
           ui->tableView->setModel(Etmp.afficher());
           //NOTIFICATION
           QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                       notifyIcon->show();


                      notifyIcon->showMessage("Ajouter ","Ajouter valide",QSystemTrayIcon::Information,15000);
               ui->lineEdit->clear();
               ui->lineEdit_2->clear();
               ui->lineEdit_3->clear();
               ui->lineEdit_4->clear();
               ui->lineEdit_5->clear();
               ui->lineEdit_6->clear();
        }
       else
           QMessageBox :: critical(nullptr,QObject::tr("NOT OK"),
                                   QObject::tr("ajout Non effectuee\n"
                                               "Click cancel o exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_3_clicked()
{
  //int CIN = ui->lineEdit_7->text().toInt();
Etmp.setCIN(ui->lineEdit_7->text().toInt());
    bool test = Etmp.supprimer(Etmp.getCIN());
   if (test)
   {
       ui->tableView->setModel(Etmp.afficher());
       //NOTIFICATION
       QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                   notifyIcon->show();


                  notifyIcon->showMessage("Suppression ","Suppression avec succes",QSystemTrayIcon::Information,15000);
            ui->lineEdit_7->clear();
    }
   else
       QMessageBox :: critical(nullptr,QObject::tr("NOT OK"),
                               QObject::tr("Suppretion Non effectuee\n"
                                           "Click cancel o exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_2_clicked()
{


    int CIN = ui->lineEdit->text().toInt();
       QString nom = ui->lineEdit_2->text();
       QString prenom = ui->lineEdit_3->text();
       QString adresse = ui->lineEdit_4->text();
       int numero = ui->lineEdit_5->text().toInt();
       QString poste = ui->lineEdit_6->text();
       Employe E(CIN,nom,prenom,adresse,numero,poste);


       if ( nom.contains(QRegExp("[^a-zA-Z]"))||nom.isEmpty() ) {
               QMessageBox::warning(this, "Erreur de saisie", "Veuillez entrer un nom valide");
                ui->lineEdit_2->clear();
           }
       if ( prenom.contains(QRegExp("[^a-zA-Z]"))||prenom.isEmpty() ) {
               QMessageBox::warning(this, "Erreur de saisie", "Veuillez entrer un prenom valide");
                ui->lineEdit_3->clear();
           }
       QRegularExpression regex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");

          if (!regex.match(adresse).hasMatch()) {
              QMessageBox::warning(this, "Erreur de saisie", "Veuillez entrer une adresse e-mail valide");
             ui->lineEdit_4->clear();
          }
          if ( poste.contains(QRegExp("[^a-zA-Z]"))||poste.isEmpty() ) {
                  QMessageBox::warning(this, "Erreur de saisie", "Veuillez entrer un poste valide");
                   ui->lineEdit_6->clear();
              }


      bool test=E.modifier(CIN);
       if(test)
       {
           QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                       notifyIcon->show();


                      notifyIcon->showMessage("Modifier ","Modification avec succes",QSystemTrayIcon::Information,15000);

   }
       else
           QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                       QObject::tr("failed.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
       ui->lineEdit->clear();
       ui->lineEdit_2->clear();
       ui->lineEdit_3->clear();
       ui->lineEdit_4->clear();
       ui->lineEdit_5->clear();
       ui->lineEdit_6->clear();
  ui->tableView->setModel(Etmp.afficher());
}


void MainWindow::on_tableView_activated(const QModelIndex &index)
{

}

void MainWindow::on_pushButton_4_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
     ui->lineEdit_7->clear();



}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{

    QString val=ui->tableView->model()->data(index).toString();

        QSqlQuery qry;
        qry.prepare("select * from employe where numero='"+val+"'");
       if (qry.exec())
       {
           while(qry.next())
           {
              ui->lineEdit_7->setText(qry.value(0).toString());


           }
       }
       else
       {
           QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                   QObject::tr("Echec"),
                   QMessageBox::Cancel);
       }
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{

    QString val=ui->tableView->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("select * from employe where CIN='"+val+"'");
       if (qry.exec())
       {
           while(qry.next())
           {
              ui->lineEdit->setText(qry.value(0).toString());
               ui->lineEdit_2->setText(qry.value(1).toString());
              ui->lineEdit_3->setText(qry.value(2).toString());
              ui->lineEdit_4->setText(qry.value(3).toString());
               ui->lineEdit_5->setText(qry.value(4).toString());
               ui->lineEdit_6->setText(qry.value(5).toString());

           }
       }
       else
       {
           QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                   QObject::tr("Echec"),
                   QMessageBox::Cancel);
       }
}


void MainWindow::on_capture_clicked()
{
    QPixmap screen_shot = ui->tabWidget->grab();
            QImage img = screen_shot.toImage();
            img.save("Capture.png");
              QDesktopServices::openUrl(QUrl("Capture.png"));
}

void MainWindow::on_pushButton_5_clicked()
{
    QPdfWriter pdf("Takwa.pdf");
            QPainter painter(&pdf);
            int i = 4000;
                   painter.setPen(Qt::red);
                   painter.setFont(QFont("Time New Roman", 25));
                   painter.drawText(3000,1400,"Liste des employees");
                   painter.setPen(Qt::black);
                   painter.setFont(QFont("Time New Roman", 15));
                   painter.drawRect(100,100,9400,2500);
                   painter.drawRect(100,3000,9400,500);
                   painter.setFont(QFont("Time New Roman", 9));
                   painter.drawText(100,3300,"CIN");
                   painter.drawText(2000,3300,"nom");
                   painter.drawText(4000,3300,"prenom");
                   painter.drawText(6000,3300,"adresse");
                    painter.drawText(8000,3300,"numero");
                    painter.drawText(10000,3300,"poste");




                   QSqlQuery query;
                   query.prepare("select * from employe");
                   query.exec();
                   while (query.next())
                   {
                       painter.drawText(100,i,query.value(0).toString());
                       painter.drawText(2000,i,query.value(1).toString());
                       painter.drawText(4000,i,query.value(2).toString());
                       painter.drawText(6000,i,query.value(3).toString());
                       painter.drawText(8000,i,query.value(4).toString());
                       painter.drawText(10000,i,query.value(0).toString());


                      i = i + 350;
                   }
            QMessageBox::information(nullptr,QObject::tr("pdf"),
                    QObject::tr("text has been written to pdf"),
                    QMessageBox::Ok);

                                QDesktopServices::openUrl(QUrl("Takwa.pdf"));
}

void MainWindow::on_radioButton_clicked()
{
    ui->tableView->setModel(Etmp.show_Desc_name());
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->tableView->setModel(Etmp.show_Asc_name());
}

void MainWindow::on_lineEdit_10_textChanged(const QString &arg1)
{
    //ui->tableView->setModel(Etmp.afficher(ui->lineEdit_10->text(), 0));
   // ui->tableView->setModel(Etmp.afficher(ui->rechercher->text()));
}

void MainWindow::on_pushButton_7_clicked()
{
    /*QString cher =ui->rechercher->text();
                ui->tableView->setModel(Etmp.chercher(cher));*/
}


void MainWindow::on_rechercher_textChanged(const QString &arg1)
{
    QString cher =ui->rechercher->text();
                ui->tableView->setModel(Etmp.chercher(cher));
}

void MainWindow::on_stat_clicked()
{
    s = new stat_combo();

      s->setWindowTitle("statistique ComboBox");
      s->choix_pie();
      s->show();
}

void MainWindow::on_pushButton_6_clicked()
{
    c = new chat();
    c1 = new chat();
    c->show();
    c1->show();
}

void MainWindow::on_radioButton_3_clicked()
{
    ui->tableView->setModel(Etmp.tri_num());
}
