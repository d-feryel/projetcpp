
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->setupUi(this);
    //QPixmap pix("C:/Users/ALYSSA/Desktop/9.png");
   // ui->label_pic->setPixmap(pix.scaled(1145,900,Qt::KeepAspectRatio));
    //ui->tabWidget->setPixmap(pix.scaled(1145,900,Qt::KeepAspectRatio));


         QString styleSheet = "QWidget#tab { background-image: url(C:/Users/FARID DJEBBI/OneDrive/Bureau/takwa.png);  background-repeat: no-repeat;  background-size:100% 100%; }";
           ui->tab->setStyleSheet(styleSheet);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int CIN2=ui->lineEdit->text().toInt();
    QString nom=ui->lineEdit_2->text();
    QString prénom=ui->lineEdit_3->text();
    int numéro=ui->lineEdit_4->text().toInt();
    QString adresse=ui->lineEdit_5->text();
    Client C(CIN2,numéro,nom,prénom,adresse);

}
