
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_stat_combo.h"
#include "recherche.h"
#include <QDate>
#include <QMessageBox>
#include <QtDebug>
#include <QString>
#include <QObject>
#include <QIntValidator>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
#include "exportexcelobject.h"
#include "quitter.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , compteur1(0)
    ,timer (new QTimer)

{
    ui->setupUi(this);
ui->numero->setValidator(new QIntValidator(100, 999, this)) ;
ui->prix->setValidator(new QIntValidator(100, 999, this)) ;

ui->tab_recherche->setModel(R.afficherRecherche());

// ui->setupUi(this);
    //QPixmap pix("C:/Users/ALYSSA/Desktop/9.png");
   // ui->label_pic->setPixmap(pix.scaled(1145,900,Qt::KeepAspectRatio));
    //ui->tabWidget->setPixmap(pix.scaled(1145,900,Qt::KeepAspectRatio));

QString styleSheet = "QWidget#tab { background-image: url(C:/Users/fayed/Desktop/takwa.png);  background-repeat: no-repeat;  background-size:100% 100%; }";

         QString styleSheet1 = "QWidget#tab_2 { background-image: url(C:/Users/fayed/Desktop/takwa.png);  background-repeat: no-repeat;  background-size:100% 100%; }";
          ui->tab->setStyleSheet(styleSheet);
           ui->tab_2->setStyleSheet(styleSheet1);
           playermusic = new QMediaPlayer;
           player = new QMediaPlayer;

           ui->lcdNumber_1->display(0);
           ui->lcdNumber_2->display(0);

         //  connect(ui->pushButton,&QPushButton::clicked,this, &MainWindow::mon_action);

           timer->start(1000);
           connect(timer,&QTimer::timeout,this, &MainWindow::action_timer);

}

MainWindow::~MainWindow()
{
    delete ui ;
}


void MainWindow::on_ajouter_clicked()
{
int NUM_R=ui->numero->text().toInt();
 QString NOM=ui->nom->text();
 QString TYPE=ui->type->currentText();
 QDate DATE_DEBUT=ui->date_debut->date();
 QDate DATE_FIN=ui->date_fin->date();
 int PRIX=ui->prix->text().toInt();


    Recherche R(NUM_R,NOM,TYPE,DATE_DEBUT,DATE_FIN,PRIX);


    bool test=R.ajouterRecherche();
    if (test)
       { QMessageBox::information(nullptr, QObject::tr("nice"),
                    QObject::tr("ajout successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_recherche->setModel(R.afficherRecherche());

    }


    else
       { QMessageBox::critical(nullptr, QObject::tr("not nice"),
                    QObject::tr("ajout failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_recherche->setModel(R.afficherRecherche());}

}


void MainWindow::on_pb_supp_clicked()
{
    Recherche R1;
    R1.setNUM_R(ui->supp->text().toUInt());
    bool test =R1.suppRecherche(R1.getNUM_R());
    if (test)
       { QMessageBox::information(nullptr, QObject::tr("nice"),
                    QObject::tr("supp successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_recherche->setModel(R.afficherRecherche());

    }


    else
       { QMessageBox::critical(nullptr, QObject::tr("not nice"),
                    QObject::tr("supp failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_recherche->setModel(R.afficherRecherche());}

}



void MainWindow::on_modifier_clicked()


{
int NUM_R=ui->numero->text().toInt();
 QString NOM=ui->nom->text();
 QString TYPE=ui->type->currentText();
 QDate DATE_DEBUT=ui->date_debut->date();
 QDate DATE_FIN=ui->date_fin->date();
 int PRIX=ui->prix->text().toInt();


    Recherche R(NUM_R,NOM,TYPE,DATE_DEBUT,DATE_FIN,PRIX);


    bool test=R.modifierRecherche();
    if (test)
       { QMessageBox::information(nullptr, QObject::tr("nice"),
                    QObject::tr("modification successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->numero->clear();
       ui->nom->clear();
     ui->type->clear();
         ui->date_debut->clear();
        ui->date_fin->clear();
       ui->prix->clear();
        ui->tab_recherche->setModel(R.afficherRecherche());

    }


    else
       { QMessageBox::critical(nullptr, QObject::tr("not nice"),
                    QObject::tr("modification failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    ui->tab_recherche->setModel(R.afficherRecherche());}

}


void MainWindow::on_tri_num_clicked()
{
     Recherche R1;
      ui->tab_recherche->setModel(R1.AfficherTrieNum());
      bool test=R.AfficherTrieNum();
      if (test)
         { QMessageBox::information(nullptr, QObject::tr("nice"),
                      QObject::tr("tri par num successful.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
          ui->tab_recherche->setModel(R.AfficherTrieNum());

      }


      else
         { QMessageBox::critical(nullptr, QObject::tr("not nice"),
                      QObject::tr("tri par num failed.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
      ui->tab_recherche->setModel(R.AfficherTrieNum());}
}

void MainWindow::on_tri_prix_clicked()
{
    Recherche R1;
     ui->tab_recherche->setModel(R1.AfficherTriePrix());

     bool test=R.AfficherTriePrix();
     if (test)
        { QMessageBox::information(nullptr, QObject::tr("nice"),
                     QObject::tr("tri par prix successful.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
         ui->tab_recherche->setModel(R.AfficherTriePrix());

     }


     else
        { QMessageBox::critical(nullptr, QObject::tr("not nice"),
                     QObject::tr("tri par prix failed.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
     ui->tab_recherche->setModel(R.AfficherTriePrix());}
}



void MainWindow::on_tri_date_clicked()
{
    Recherche R1;
     ui->tab_recherche->setModel(R1.AfficherTrieDate_fin());

     bool test=R.AfficherTrieDate_fin();
     if (test)
        { QMessageBox::information(nullptr, QObject::tr("nice"),
                     QObject::tr("tri par date successful.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
         ui->tab_recherche->setModel(R.AfficherTrieDate_fin());

     }


     else
        { QMessageBox::critical(nullptr, QObject::tr("not nice"),
                     QObject::tr("tri par date failed.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
     ui->tab_recherche->setModel(R.AfficherTrieDate_fin());}

}

void MainWindow::on_chercher_num_textChanged(const QString &arg1)
{
    Recherche R1;
    ui->tab_recherche->setModel(R1.rechercherNUM_R(arg1));

}

void MainWindow::on_chercher_prix_textChanged(const QString &arg1)
{
    Recherche R1;
    ui->tab_recherche->setModel(R1.rechercherPRIX(arg1));

}

void MainWindow::on_pdf_clicked()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
           if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

           QPrinter printer(QPrinter::PrinterResolution);
           printer.setOutputFormat(QPrinter::PdfFormat);
           printer.setPaperSize(QPrinter::A4);
           printer.setOutputFileName(fileName);



           QSqlQuery q;
           q.prepare("SELECT * FROM RECHERCHE ");
           q.exec();
           QString pdf="<br> <img src='C:/Users/fayed/Desktop/esprit.png' height='130' width='150'/> <tr> <th> < img src='C:/Users/fayed/Desktop/LOGO.png' height='60' width='110'/></th> </tr> <h1  style='color:red'>LISTE DES RECHERCHE  <br></h1>\n <br> <table>  <tr>  <th> Numero de Recherche </th>  <th>  Date debut  </th> <th> Type </th>  <th> NOM </th> <th> Date fin </th> <th>prix </th>  </tr>" ;


           while ( q.next()) {

               pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+"</td>     <td>" + q.value(4).toString() +"</td>   <td>" +q.value(1).toString() +"  "" " "</td>   <td>"+q.value(2).toString()+"</td>   <td>"+q.value(3).toString()+" "   " " "</td> <td> "+q.value(5).toString()+" "   " " "</td> " ;

           }
           QTextDocument doc;
           doc.setHtml(pdf);
           doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
           doc.print(&printer);


}


void MainWindow::on_start_clicked()
{
    playermusic->setMedia(QUrl::fromLocalFile("C:/Users/fayed/Desktop/flower.mp3"));
    playermusic->play();
    qDebug() << playermusic->errorString();
}

void MainWindow::on_pause_clicked()
{
    playermusic->pause();

}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
       playermusic->setVolume(position);
}

void MainWindow::on_pb_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->tab_recherche);

    //colums to export
    obj.addField(0, "num", "char(20)");
    obj.addField(1, "nom", "char(20)");
    obj.addField(2, "type", "char(20)");
    obj.addField(3, "d.debut", "char(20)");
    obj.addField(4, "d.fin", "char(20)");
    obj.addField(5, "prix", "char(20)");
   // obj.addField(5, "timeedit", "char(20)");


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}

void MainWindow::on_stat_clicked()
{
    s = new stat_combo();

  s->setWindowTitle("statistique ComboBox");
  s->choix_pie();
  s->show();

}

void MainWindow::on_tab_recherche_clicked(const QModelIndex &index)
{
    QString val=ui->tab_recherche->model()->data(index).toString();
            QSqlQuery qry;
            qry.prepare("select * from RECHERCHE where NUM_R='"+val+"'");
           if (qry.exec())
           {
               while(qry.next())
               {
                  ui->numero->setText(qry.value(0).toString());
                   ui->nom->setText(qry.value(1).toString());
                  ui->type->setCurrentText(qry.value(2).toString());
                  ui->date_debut->setDate(qry.value(3).toDate());
                   ui->date_fin->setDate(qry.value(4).toDate());
                   ui->prix->setText(qry.value(5).toString());

               }
           }
           else
           {
               QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                       QObject::tr("Echec"),
                       QMessageBox::Cancel);
           }
}

void MainWindow::on_Facture_clicked()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
           if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

           QPrinter printer(QPrinter::PrinterResolution);
           printer.setOutputFormat(QPrinter::PdfFormat);
           printer.setPaperSize(QPrinter::A4);
           printer.setOutputFileName(fileName);



           QSqlQuery q;
           q.prepare("SELECT NUM_R ,DATE_DEBUT,PRIX ,((7 * PRIX)/100+PRIX) ,DATE_FIN FROM RECHERCHE ");
           q.exec();
           QString pdf="<br> <img src='C:/Users/fayed/Desktop/esprit.png' height='130' width='150'/> <tr> <th> < img src='C:/Users/fayed/Desktop/LOGO.png' height='60' width='110'/></th> </tr> <h1  style='color:red'>FACTURE  <br></h1>\n <br> <table>  <tr>  <th> Numero de Facture </th>  <th> date de facture  </th>  <th> Date limite de paiement  </th><th> Total HT en DT </th>  <th>  </th> <th> Total TTC en DT  </th>  </tr>" ;


           while ( q.next()) {

               pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+"</td>     <td>" + q.value(4).toString() +"</td>   <td>" +q.value(1).toString() +"  "" " "</td>   <td>"+q.value(2).toString()+"</td>   <td>"+q.value(3).toString()+" "   " " "</td> <td> "+q.value(5).toString()+" "   " " "</td> " ;

           }
           QTextDocument doc;
           doc.setHtml(pdf);
           doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
           doc.print(&printer);

}

void MainWindow::mon_action()
{
    //incrementer le compteur a chaque clique du bouton
   // compteur1++;
    ui->lcdNumber_1->display(compteur1);

}

void MainWindow::action_timer()
{
    //a chaque tick , incrementer le compteur et afficher sur lcd 2

   static int compteur=0;

   compteur++;
   ui->lcdNumber_2->display(compteur);
 if (compteur>59)
 {
     compteur1=compteur1+1;
     ui->lcdNumber_1->display(compteur1);
     compteur=0;

}
}

void MainWindow::on_camera_clicked()
{
    c= new camera();
    c->show();
}

void MainWindow::on_retour_clicked()
{
    quitter afficher;
    afficher.setModal(true);
    afficher.exec();
}

void MainWindow::on_capture2_clicked()
{
    QPixmap screen_shot = ui->lcdNumber_1->grab();
    QImage img = screen_shot.toImage();

            img.save("Capture.png");
              QDesktopServices::openUrl(QUrl("Capture.png"));
}
