
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recherche.h"
#include <QDate>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->setupUi(this);
    //QPixmap pix("C:/Users/ALYSSA/Desktop/9.png");
   // ui->label_pic->setPixmap(pix.scaled(1145,900,Qt::KeepAspectRatio));
    //ui->tabWidget->setPixmap(pix.scaled(1145,900,Qt::KeepAspectRatio));


         QString styleSheet = "QWidget#tab { background-image: url(C:/Users/fayed/Desktop/takwa.png);  background-repeat: no-repeat;  background-size:100% 100%; }";
           ui->tab->setStyleSheet(styleSheet);

}

MainWindow::~MainWindow()
{
    delete ui ;
}


void MainWindow::on_ajouter_clicked()
{
int NUM_R=ui->numero->text().toInt();
 QString NOM=ui->nom->text();
 QString TYPE=ui->type->text();
 QDate DATE_DEBUT=ui->date_debut->date();
 QDate DATE_FIN=ui->date_fin->date();
 int PRIX=ui->prix->text().toInt();


    Recherche R(NUM_R,NOM,TYPE,DATE_DEBUT,DATE_FIN,PRIX);
}
