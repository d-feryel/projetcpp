
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "evenement.h"
#include <QString>
#include <QDate>
#include <QtDebug>
#include <QMessageBox>
#include <QIntValidator>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>
#include<QSystemTrayIcon>
#include <QRegExp>

#include <QFileDialog>
#include <QPainter>

#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>
#include <QApplication>
#include "smtp.h"

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QtDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>
#include <QApplication>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QtCore>
#include <QtNetwork>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    ui->setupUi(this);
    ui->le_ref->setValidator (new QIntValidator(0, 9999999, this));
    ui->le_nb_p->setValidator (new QIntValidator(0, 9999999, this));
    ui->le_budget->setValidator (new QIntValidator(0, 9999999, this));

    ui->tab_events_2->setModel(E.afficher_event());

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
     QDate dd=ui->le_dd->date();
     QDate df=ui->le_df->date();
     QString lieu=ui->le_lieu->currentText();
     float budget=ui->le_budget->text().toFloat();
     int nb_p=ui->le_nb_p->text().toInt();


   Evenement e(ref,nb_p,dd,df,lieu,budget);
   bool test=e.ajouter_event();
   if (test)
   {
       QMessageBox::information(nullptr, QObject::tr("OK"),
                                QObject::tr("Ajout éffectué\n"
                                            "Click Cancel to exit"),QMessageBox::Cancel);
       ui->tab_events_2->setModel(e.afficher_event());

   }
   else
       QMessageBox::critical(nullptr, QObject::tr(" NOT OK"),
                                QObject::tr("Ajout non éffectué\n"
                                            "Click Cancel to exit"),QMessageBox::Cancel);
       ui->tab_events->setModel(e.afficher_event());
       ui->le_dd->clear();
       ui->le_ref->clear();
       ui->le_df->clear();
       ui->le_nb_p->clear();
       ui->le_budget->clear();

}

void MainWindow::on_pb_supp_event_clicked()
{
    //int ref = ui->supp_ref;
    Evenement E1; E1.setref(ui->supp_ref->text().toInt());
    bool test=E1.supprimer_event(E1.getref());
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression éffectuée\n"
                                             "Click Cancel to exit"),QMessageBox::Cancel);
         ui->tab_events_2->setModel(E.afficher_event());

    }
    else
        QMessageBox::critical(nullptr, QObject::tr(" NOT OK"),
                                 QObject::tr("Suppression non éffectuée\n"
                                             "Click Cancel to exit"),QMessageBox::Cancel);

}

void MainWindow::on_pb_modify_clicked()
{


    int ref=ui->le_ref->text().toInt();
    QDate dd=ui->le_dd->date();
    QDate df=ui->le_df->date();
    QString lieu=ui->le_lieu->currentText();
    float budget=ui->le_budget->text().toFloat();
    int nb_p=ui->le_nb_p->text().toInt();

    Evenement e(ref,nb_p,dd,df,lieu,budget);

  bool test=e.modifier_event();
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("modification éffectué\n"
                                             "Click Cancel to exit"),QMessageBox::Cancel);
        ui->tab_events_2->setModel(e.afficher_event());

    }
    else
        QMessageBox::critical(nullptr, QObject::tr(" NOT OK"),
                                 QObject::tr("modification non éffectué\n"
                                             "Click Cancel to exit"),QMessageBox::Cancel);
        ui->tab_events->setModel(e.afficher_event());
        ui->le_dd->clear();
        ui->le_ref->clear();
        ui->le_df->clear();
        ui->le_nb_p->clear();
        ui->le_budget->clear();
}


void MainWindow::on_le_chercher_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM EVENEMENT WHERE REF  LIKE'"+arg1+"%' or LIEU  LIKE'"+arg1+"%' or BUDGET LIKE'"+arg1+"%'");
     query->exec();
     if (query->next()) {
     model->setQuery(*query);
     ui->tab_events_2->setModel(model);
     }
     else {
         QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                         QObject::tr("NO MATCH FOUND !!\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
      ui->le_chercher->clear();}
}

void MainWindow::on_pushButton_4_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    qDebug()<<dir;
    QPdfWriter pdf(dir+"/PdfList.pdf");
                           QPainter painter(&pdf);
                          int i = 4000;

                                painter.drawPixmap(QRect(100,100,2500,2500),QPixmap("C:/Users/youss/Downloads/LOGO ESPRIT.png"));
                               // painter.drawText(900,650,"Smart Charging Station");
                               painter.setPen(Qt::blue);
                               painter.setFont(QFont("Time New Roman", 25));
                               painter.drawText(3000,1400,"Liste des EVENEMENT");
                               painter.setPen(Qt::black);
                               painter.setFont(QFont("Time New Roman", 15));
                               painter.drawRect(100,100,9400,2500); // dimension mtaa3 rectangle li fih liste
                               painter.drawRect(100,3000,9400,500);
                               painter.setFont(QFont("Time New Roman", 9));
                               painter.drawText(300,3300,"REF");
                               painter.drawText(2000,3300,"NB_P");
                               painter.drawText(4000,3300,"DD");
                               painter.drawText(5600,3300,"DF");
                               painter.drawText(8000,3300,"LIEU");
                               painter.drawText(8700,3300,"BUDGET");

                               painter.drawRect(100,3000,9400,10700);
                               //QTextDocument previewDoc;
                               QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");
                               //QTextCursor cursor(&previewDoc);
                               QSqlQuery query;
                               query.prepare("select * from EVENEMENT");
                               query.exec();
                               while (query.next())
                               {
                                   painter.drawText(300,i,query.value(0).toString());
                                   painter.drawText(2000,i,query.value(1).toString());
                                   painter.drawText(4000,i,query.value(2).toString());
                                   painter.drawText(5600,i,query.value(3).toString());
                                   painter.drawText(8000,i,query.value(4).toString());
                                   painter.drawText(8700,i,query.value(5).toString());
                                  i = i +900;
                               }
                               int reponse = QMessageBox::question(this, "Générer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                   QMessageBox::Yes|QMessageBox::No);
                                   if (reponse == QMessageBox::Yes)
                                   {
                                       QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));

                                       painter.end();
                                   }
                                   else
                                   {
                                        painter.end();
                                   }
}

void MainWindow::on_radioButton_clicked()
{
 ui->tab_events_2->setModel(E.trie_ref());
}

void MainWindow::on_radioButton_2_clicked()
{
ui->tab_events_2->setModel(E.trie_lieu());
}

void MainWindow::on_radioButton_3_clicked()
{
ui->tab_events_2->setModel(E.trie_nb_p());
}

void MainWindow::on_Stats_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                                    model->setQuery("select * from EVENEMENT where LIEU = 'Tunis' ");
                                    float e=model->rowCount();
                                    model->setQuery("select * from EVENEMENT where LIEU = 'Sfax' ");
                                    float ee=model->rowCount();
                                    model->setQuery("select * from EVENEMENT where LIEU = 'Sousse' ");
                                    float eee=model->rowCount();
                                    float total=e+ee+eee;
                                    QString a=QString("Tunis"+QString::number((e*100)/total,'f',2)+"%" );
                                    QString b=QString("Sousse"+QString::number((ee*100)/total,'f',2)+"%" );
                                    QString c=QString("Sfax"+QString::number((eee*100)/total,'f',2)+"%" );
                                    QPieSeries *series = new QPieSeries();
                                    series->append(a,e);
                                    series->append(b,ee);
                                    series->append(c,eee);
                            if (e!=0)
                            {QPieSlice *slice = series->slices().at(0);
                             slice->setLabelVisible();
                             slice->setPen(QPen());}
                            if ( ee!=0)
                            {
                                     // Add label, explode and define brush for 2nd slice
                                     QPieSlice *slice1 = series->slices().at(1);
                                     //slice1->setExploded();
                                     slice1->setLabelVisible();
                            }
                            if ( eee!=0)
                            {
                                     // Add label, explode and define brush for 2nd slice
                                     QPieSlice *slice2 = series->slices().at(2);
                                     //slice1->setExploded();
                                     slice2->setLabelVisible();
                            }
                                    // Create the chart widget
                                    QChart *chart = new QChart();
                                    // Add data to chart with title and hide legend
                                    chart->addSeries(series);
                                    chart->setTitle("Pourcentage des Lieux : nombre total : "+ QString::number(total));
                                    chart->legend()->hide();
                                    // Used to display the chart
                                    QChartView *chartView = new QChartView(chart);
                                    chartView->setRenderHint(QPainter::Antialiasing);
                                    chartView->resize(1000,500);
                                    chartView->show();
}

void MainWindow::on_tab_events_activated(const QModelIndex &index)
{
    QString val=ui->tab_events_2->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM EVENEMENT WHERE ref='"+val+"' OR nb_p='"+val+"' OR budget='"+val+"'");
    if (qry.exec())
    { while (qry.next())
        {
            //update
            //id
            ui->le_ref->setText(qry.value(0).toString());
            ui->le_nb_p->setText(qry.value(1).toString());
             ui->le_budget->setText(qry.value(5).toString());

            //delete
            //id
            ui->supp_ref->setText(qry.value(0).toString()); //pour supprimer


        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    qDebug() << QSslSocket::sslLibraryBuildVersionString();
    qDebug() << QSslSocket::sslLibraryVersionString();
    qDebug() << QSslSocket::supportsSsl();
    Smtp * smtp = new Smtp("jihedhorchani@gmail.com" , "pwnpdldwbcokcmcw", "smtp.gmail.com",465);
            connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

           QString msg=ui->msgmail->toPlainText();

            smtp->sendMail("ilyes_test","youssef.grissa.yg@gmail.com",ui->lineEdit_13->text(),msg);

            QMessageBox::information(nullptr, QObject::tr("SENT"),
                                     QObject::tr("Email Sended Successfully.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    QDate datee=ui->calendarWidget->selectedDate();
           qDebug() << datee;
           QDate d= datee;
           qDebug() << d;
           QSqlQuery query;
           query.prepare("SELECT ref,nb_p,dd,df,lieu,budget from EVENEMENT where dd = :date");
           query.bindValue(":date",d);
           query.exec();
           QSqlQueryModel * model=new QSqlQueryModel();


                 model->setQuery(query);
                 model->setHeaderData(0, Qt::Horizontal, QObject::tr("Reference"));
                 model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nombre de Participants"));
                 model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date de début"));
                 model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de fin"));
                 model->setHeaderData(4, Qt::Horizontal, QObject::tr("Le Lieu"));
                 model->setHeaderData(5, Qt::Horizontal, QObject::tr("Le Budget"));
                ui->tab_events->setModel(model);
              //  ui->tab_events->setModel(E.afficher_event());


}

void MainWindow::on_tab_events_2_activated(const QModelIndex &index)
{
    QString val=ui->tab_events_2->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM EVENEMENT WHERE ref='"+val+"' OR nb_p='"+val+"' OR budget='"+val+"'");
    if (qry.exec())
    { while (qry.next())
        {
            //update
            //id
            ui->le_ref->setText(qry.value(0).toString());
            ui->le_nb_p->setText(qry.value(1).toString());
             ui->le_budget->setText(qry.value(5).toString());

            //delete
            //id
            ui->supp_ref->setText(qry.value(0).toString()); //pour supprimer


        }
    }
}
