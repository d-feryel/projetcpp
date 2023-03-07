
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "evenement.h"
#include <QString>
#include <QDate>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    ui->setupUi(this);
   // QPixmap pix("C:/Users/youss/OneDrive/Bureau/background.png");
   // ui->label_pic->setPixmap(pix.scaled(1145,900,Qt::KeepAspectRatio));
    //ui->tabWidget->setPixmap(pix.scaled(1145,900,Qt::KeepAspectRatio));


         QString styleSheet = "QWidget#tab { background-image: url(C:/Users/youss/OneDrive/Bureau/background.png);  background-repeat: no-repeat;  background-size:100% 100%; }";
           ui->tab->setStyleSheet(styleSheet);



}






MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
     int ref=ui->le_ref->text().toInt();
     QDate dd=ui->le_dd->text().Date();
     QDate df=ui->le_df->text().Date();
     QString lieu=ui->le_lieu->text();
     float budget=ui->le_budget->text().toFloat();
     int nb_p=ui->le_nb_p->text().toInt();


   Evenement e(ref,nb_p,dd,df,lieu,budget);
}
