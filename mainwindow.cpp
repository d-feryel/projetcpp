#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"equipement.h"
#include <QPushButton>
#include <QTimer>
#include <QtDebug>
#include <QSqlQueryModel>
#include<QImage>
#include<QSqlQuery>
#include <QTabWidget>
#include<QMessageBox>
#include  <QLineEdit>
#include  <QPlainTextEdit>
#include <QTextEdit>
#include <QDate>
#include<QMessageBox>
#include<QPainter>
#include<QtPrintSupport/QPrinter>
#include<QFile>
#include<QFileDialog>
#include<QPainter>
#include <qrcode.h>
#include <QPixmap>
#include<QDirModel>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QSvgRenderer>
#include <fstream>
#include<QRegularExpression>
#include <QPainter>
#include <QPdfWriter>
#include "qrcode.h"
#include <QIntValidator>
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
#include<ui_dumessengerconnectiondialog.h>


using qrcodegen::QrCode ;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)


{


     equipement eq;
     ui->tableView->setModel(eq.afficher());
     ui->histo->setModel(eq.afficher_historique0());

     ui->lineEdit_ref->setValidator(new QIntValidator(1, 999, this));
     ui->lineEdit_nomeq->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+")));
     ui->lineEdit_quant->setValidator(new QIntValidator(1, 999999, this));
     ui->lineEdit_prixeq->setValidator(new QIntValidator(1, 999999, this));



      QString styleSheet = "QWidget#tab { background-image: url(C:/Users/Yefa/Downloads/takwa.png);  background-repeat: no-repeat;  background-size:100% 100%; }";
       ui->tab->setStyleSheet(styleSheet);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    int nref = ui->lineEdit_ref->text().toInt();
    QDate dateq =ui->dateq->date();
     QString nomeq= ui->lineEdit_nomeq->text();
     int qant = ui->lineEdit_quant->text().toInt();
     QString descr = ui->lineEdit_prixeq_2->text();//lineEdit_prix_2=description
      int prix = ui->lineEdit_prixeq->text().toInt();


        equipement eq(nref,dateq,nomeq,qant,descr,prix) ;

     bool test=eq.ajouter();
     ui->tableView->setModel(eq.afficher());
eq.ajouter_historique("ajout",ui->lineEdit_ref->text().toInt(),ui->lineEdit_nomeq->text());
ui->histo->setModel(eq.afficher_historique0());

     if(test)
     {
      QMessageBox::information(nullptr,QObject::tr("L'ajout d'un equipement"),QObject::tr("AJOUT EFFECTUER.\n" "click Cancel to exit."), QMessageBox::Cancel);

     }
     else
         QMessageBox::critical(nullptr, QObject::tr("Ajout non effecutée"),QObject::tr("AJOUT NON EFFECTUER.\n " "click Cancel to exit ."), QMessageBox::Cancel);

    }





void MainWindow::on_supp_eq_clicked()
{

equipement eq;
    int nref = ui->lineEdit_ref->text().toInt();

     bool test=eq.supprimer(nref);


     if(test)
     {
          ui->tableView->setModel(eq.afficher());
          eq.ajouter_historique("suppresion",ui->lineEdit_ref->text().toInt(),ui->lineEdit_nomeq->text());
         ui->histo->setModel(eq.afficher_historique0());
    QMessageBox :: information (nullptr, QObject ::tr("OK"),
                  QObject ::tr("suppression effectué\n"
                               "click cancel to exit"),
             QMessageBox:: Cancel);

}
 else
 {
     QMessageBox::critical(nullptr,QObject::tr("not ok"),
                          QObject::tr("try again.\n"
                                      "click cancel to exit."),QMessageBox::Cancel);
 }
}





void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();

            QSqlQuery qry;
            qry.prepare("select * from EQUIPEMENT where NREF='"+val+"' " );

            if(qry.exec())
            {
                while(qry.next())
                {
                    ui->lineEdit_ref->setText(qry.value(0).toString());
                      ui->dateq->setDateTime(qry.value(1).toDateTime());
                    ui->lineEdit_nomeq->setText(qry.value(2).toString());
                     ui->lineEdit_quant->setText(qry.value(3).toString());
                     ui->lineEdit_prixeq_2->setText(qry.value(4).toString());

                     ui->lineEdit_prixeq->setText(qry.value(5).toString());
                }
        }
            //generer code QR
            QString text ="equipement details :"+ ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),1)).toString()
                    +" "+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),2)).toString()
                    +" "+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),3)).toString()
                    +" "+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),4)).toString();
                 +" "+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),5)).toString();
                 +" "+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),6)).toString();
            using namespace qrcodegen;
              // Create the QR Code object
              QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );
              qint32 sz = qr.getSize();
              QImage im(sz,sz, QImage::Format_RGB32);
                QRgb black = qRgb(  0,  0,  0);
                QRgb white = qRgb(255,255,255);
              for (int y = 0; y < sz; y++)
                for (int x = 0; x < sz; x++)
                  im.setPixel(x,y,qr.getModule(x, y) ? black : white );
              ui->QR_code->setPixmap( QPixmap::fromImage(im.scaled(256,256,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
}





void MainWindow::on_modif_eq_clicked()
{
    ui->lineEdit_ref->setValidator(new QIntValidator(1, 999, this));
     ui->lineEdit_nomeq->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+")));
    ui->lineEdit_quant->setValidator(new QIntValidator(1, 999999, this));
    ui->lineEdit_prixeq_2->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+")));
    ui->lineEdit_prixeq->setValidator(new QIntValidator(1, 999999, this));

    int nref = ui->lineEdit_ref->text().toInt();
    QDate dateq =ui->dateq->date();
     QString nomeq= ui->lineEdit_nomeq->text();
     int qant = ui->lineEdit_quant->text().toInt();
     QString descr = ui->lineEdit_prixeq_2->text();//lineEdit_prix_2=description
      int prix = ui->lineEdit_prixeq->text().toInt();
    equipement eq(nref,dateq,nomeq,qant,descr,prix);
    bool test1=eq.modifier();
                   QMessageBox msgBox;
                   if (test1)
{
                       msgBox.setText("modifier avec succes");
  eq.ajouter_historique("modification",ui->lineEdit_ref->text().toUInt(),ui->lineEdit_nomeq->text());
    ui->histo->setModel(eq.afficher_historique0());
                   ui->lineEdit_ref->clear();
                   ui->dateq->clearMaximumDate();
                   ui->lineEdit_nomeq->clear();
                   ui->lineEdit_quant->clear();
                   ui->lineEdit_prixeq_2->clear();
                   ui->lineEdit_prixeq->clear();
 }

                             else
                               msgBox.setText("echec de de modifier");
                           msgBox.exec();
                            ui->tableView->setModel(eq.afficher());




}

void MainWindow::on_triref_clicked()
{
    equipement eq;
    ui->tableView->setModel(eq.trier_ref());
}

void MainWindow::on_triprix_clicked()
{
    equipement eq;
    ui->tableView->setModel(eq.trier_prix());
}


void MainWindow::on_triqant_clicked()
{
    equipement eq;
    ui->tableView->setModel(eq.trier_qant());
}




void MainWindow::on_exp_pdf_clicked()
{
    QString strStream;
              strStream = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
                  if (QFileInfo(strStream).suffix().isEmpty())
                      { strStream.append(".pdf"); }

                  QPrinter printer(QPrinter::PrinterResolution);
                  printer.setOutputFormat(QPrinter::PdfFormat);
                  printer.setPaperSize(QPrinter::A4);
                  printer.setOutputFileName(strStream);

                        QTextStream out(&strStream);

                        const int rowCount = ui->tableView->model()->rowCount();
                        const int columnCount = ui->tableView->model()->columnCount();
                        QString TT = QDateTime::currentDateTime().toString();
                        out <<"<html>\n"
                              "<head>\n"
                               "<meta Content=\"Text/html; charset=Windows-1251\">\n"

                            << "<title>ERP - EQUIPEMENT LIST<title>\n "
                            << "</head>\n"
                            "<body bgcolor=#FFFFFF link=#5000A0>\n"
                               "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                              +"<img src=C:\\Users\\Yefa\\Pictures\\pdf\\pic.png />" //path
                            "<h1 style=\"text-align: center;\"><strong> - LISTE DES EQUIPEMENTS -  </strong></h1>";

                               out << "<img src=\"" << "C:\\Users\\Yefa\\Desktop\\pic.png"<< "\"/>\n"
                            "<table style=\"text-align: center; font-size: 10px;\" border=1>\n "
                              "</br> </br>";
                        // headers
                        out << "<thead><tr bgcolor=#F0F8FF>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->tableView->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";

                        // data table
                        for (int row = 0; row < rowCount; row++) {
                            out << "<tr>";
                            for (int column = 0; column < columnCount; column++)
                          {
                                if (!ui->tableView->isColumnHidden(column)) {
                                    QString data =ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;")); //pas compriis
                                }
                            }
                            out << "</tr>\n";
                        }
                        out <<  "</table>\n"

                            "</body>\n"
                            "</html>\n";

                        QTextDocument document;
                        document.setHtml(strStream);
                        document.print(&printer);
}

void MainWindow::on_stat_clicked()
{
    s = new stat_combo();

          s->setWindowTitle("statistique ComboBox");
          s->choix_pie();
          s->show();
}




void MainWindow::on_recher_textChanged(const QString &arg1)
{
    ui->recher->setValidator(new QIntValidator(1, 999, this));
    equipement eq;
    QString cher =ui->recher->text();
                    ui->tableView->setModel(eq.chercher(cher));
}



void MainWindow::on_his_but_clicked()
{


       equipement eq;
        QString type=ui->typehistorique->currentText();
        ui->histo->setModel(eq.afficher_historique(type));


}

void MainWindow::on_histo_activated(const QModelIndex &index)
{

    QString val=ui->histo->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT *from history where nref='"+val+"' ");

}

void MainWindow::on_aff_clicked()
{
    equipement eq;
     QString type=ui->typehistorique->currentText();
     ui->histo->setModel(eq.afficher_historique(type));

}

void MainWindow::on_listView_activated(const QModelIndex &index)
{
    QString val=ui->histo->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT *from history where id='"+val+"' ");


}

void MainWindow::on_typehistorique_2_currentIndexChanged(const QString &arg1)
{
    //
}

void MainWindow::on_suphis_clicked()
{
    QSqlQuery query;

         query.prepare("DELETE from history");

    query.exec();
}
/////////////////////////////TAKWA////////////////////////////////////////////////////////
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


void MainWindow::on_supp_emp_clicked()
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

void MainWindow::on_modif_emp_clicked()
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

void MainWindow::on_reset_emp_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
     ui->lineEdit_7->clear();


}

void MainWindow::on_tableView_emp_clicked(const QModelIndex &index)
{
    QString val=ui->tableView_emp->model()->data(index).toString();

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

void MainWindow::on_tableView_emp_doubleClicked(const QModelIndex &index)
{
    QString val=ui->tableView_emp->model()->data(index).toString();
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

void MainWindow::on_capture_emp_clicked()
{
    QPixmap screen_shot = ui->tabWidget->grab();
            QImage img = screen_shot.toImage();
            img.save("Capture.png");
              QDesktopServices::openUrl(QUrl("Capture.png"));
}

void MainWindow::on_pdf_emp_clicked()
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

void MainWindow::on_radio_nom_emp_clicked()
{
    ui->tableView_emp->setModel(Etmp.show_Desc_name());
}

void MainWindow::on_radio_cin_emp_clicked()
{
    ui->tableView_emp->setModel(Etmp.show_Asc_name());
}

void MainWindow::on_rechercher_emp_textChanged(const QString &arg1)
{
    QString cher =ui->rechercher_emp->text();
                ui->tableView_emp->setModel(Etmp.chercher(cher));
}

void MainWindow::on_stat_emp_clicked()
{
    s = new stat_combo();

      s->setWindowTitle("statistique ComboBox");
      s->choix_pie();
      s->show();
}
/*
void MainWindow::on_chat_emp_clicked()
{
    c = new chat();
    c1 = new chat();
    c->show();
    c1->show();
}
*/
void MainWindow::on_radio_num_emp_clicked()
{
    ui->tableView_emp->setModel(Etmp.tri_num());
}
