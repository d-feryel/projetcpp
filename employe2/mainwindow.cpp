
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clients.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QIntValidator>
#include <QSqlQuery>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>
#include <QFileDialog>
#include <iostream>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QAuthenticator>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QString styleSheet = "QWidget#tab { background-image: url(C:/Users/FARID DJEBBI/OneDrive/Bureau/takwa.png);  background-repeat: no-repeat;  background-size:100% 100%; }";
          ui->tab->setStyleSheet(styleSheet);
    ui->le_cin->setValidator (new QIntValidator(0, 9999999, this));
    ui->le_num->setValidator (new QIntValidator(0, 9999999, this));
    //ui->tab_client->setModel(c.afficher());
    ui->tab_client->setModel(c.afficher());

    int ret = A.connectArduino();
        qDebug() << ret;
        switch(ret){
            case 0:
                qDebug() << ret;
                qDebug() << "arduino is abailable and connected to: " << A.getArduinoPortName();
            break;
            case 1 :
                qDebug() << ret;
                qDebug() << "arduino is available but not connected to :  " << A.getArduinoPortName();
            break;
            case -1:
                qDebug() << ret;
                qDebug() << "arduino is not available";
            break;
        }
        QObject::connect(A.getSerial(), SIGNAL(readyRead()), this, SLOT(addGasState()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajout_clicked()
{
    int cin2=ui->le_cin->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    int num=ui->le_num->text().toInt();
    //QString adresse=ui->le_adresse->text();
    QString adresse=ui->le_adresse_2->currentText();



    Clients c(cin2,nom,prenom,num,adresse);

   bool test=c.ajouter();
   if(test)
   {
       QMessageBox::information(nullptr, QObject::tr("OK"),
                               QObject::tr("ajout successful.\n"
                                           "click cancel to exit."),QMessageBox::Cancel);
    ui->tab_client->setModel(c.afficher());
    stat();
   }
   else QMessageBox::critical(nullptr, QObject::tr(" not OK"),
                                 QObject::tr("ajout non effectue.\n"
                                             "click cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_supprimer_clicked()
{
    Clients c1; c1.setcin2(ui->le_cin->text().toInt());
        bool test=c1.supprimer(c1.getcin2());
        QMessageBox msgbox;
        if(test) {msgbox.setText("suppression avec succes");
       ui->tab_client->setModel(c1.afficher());
        }
        else msgbox.setText("echec de suppression");
        msgbox.exec();
        ui->tab_client->setModel(c.afficher());

}

void MainWindow::on_modifier_clicked()
{
    int cin2=ui->le_cin->text().toInt();
    if (ui->le_cin->text().isEmpty()) { // Vérifie si cin est vide
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le champ Cin ne doit pas être vide."));
        return;
    }
    int num=ui->le_num->text().toInt();
QString nom=ui->le_nom->text();
if (nom.isEmpty()) { // vérifie si nom est vide
    QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le champ nom doit être non vide."));
    return;
}
    QString prenom=ui->le_prenom->text();
    if (prenom.isEmpty()) { // vérifie si prenom est vide
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le champ prenom doit être non vide."));
        return;
    }

    QString adresse=ui->le_adresse_2->currentText();





    Clients c(cin2,nom,prenom,num,adresse);

     bool test=c.modifier(cin2,nom,prenom,num,adresse);
     if(test)
     {ui->tab_client->setModel(c.afficher());
         stat();
         QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("modif successful.\n"
                                             "click cancel to exit."),QMessageBox::Cancel);

     }
     else QMessageBox::critical(nullptr, QObject::tr(" not OK"),
                                   QObject::tr("modif non effectue.\n"
                                               "click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pdf_clicked()
{

    QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tab_client->model()->rowCount();
                const int columnCount =ui->tab_client->model()->columnCount();


                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("eleve")
                        <<  "</head>\n"
                        "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                            "<h1>Liste des Evenements</h1>"

                            "<table border=1 cellspacing=0 cellpadding=2>\n";

                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tab_client->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tab_client->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tab_client->isColumnHidden(column)) {
                                   QString data = ui->tab_client->model()->data(ui->tab_client->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";



        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);


        //QTextDocument document;
        //document.setHtml(html);
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("mypdffile.pdf");
        document->print(&printer);

}



void MainWindow::on_tri_clicked()
{
    Clients c1;
          ui->tab_client->setModel(c1.AfficherTrieNum());
          bool test=c1.AfficherTrieNum();
          if (test)
             { QMessageBox::information(nullptr, QObject::tr("nice"),
                          QObject::tr("tri par num successful.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
              ui->tab_client->setModel(c1.AfficherTrieNum());

          }


          else
             { QMessageBox::critical(nullptr, QObject::tr("not nice"),
                          QObject::tr("tri par num failed.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
          ui->tab_client->setModel(c1.AfficherTrieNum());}
    }


void MainWindow::on_pdf_3_clicked()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
               if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

               QPrinter printer(QPrinter::PrinterResolution);
               printer.setOutputFormat(QPrinter::PdfFormat);
               printer.setPaperSize(QPrinter::A4);
               printer.setOutputFileName(fileName);



               QSqlQuery q;
               q.prepare("SELECT * FROM Clients ");
               q.exec();
               QString pdf="<br> <img src='C:/Users/fayed/Desktop/esprit.png' height='130' width='150'/> <tr> <th> < img src='C:/Users/fayed/Desktop/LOGO.png' height='60' width='110'/></th> </tr> <h1  style='color:red'>LISTE DES clients  <br></h1>\n <br> <table>  <tr>  <th> cin </th>  <th>  nom  </th> <th> prenom </th>  <th> num </th> <th> adress </th> <th>i </th>  </tr>" ;


               while ( q.next()) {

                   pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+"</td>     <td>" + q.value(4).toString() +"</td>   <td>" +q.value(1).toString() +"  "" " "</td>   <td>"+q.value(2).toString()+"</td>   <td>"+q.value(3).toString()+" "   " " "</td> <td> "+q.value(5).toString()+" "   " " "</td> " ;

               }
               QTextDocument doc;
               doc.setHtml(pdf);
               doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
               doc.print(&printer);
}

void MainWindow::on_chercher_num_textChanged(const QString &arg1)
{
    Clients c1;
        ui->tab_client->setModel(c1.rechercherNUM(arg1));
}

// stat


void MainWindow::on_pushButton_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                                    model->setQuery("select * from Clients where Adresse = 'Tunis' ");
                                    float e=model->rowCount();
                                    model->setQuery("select * from Clients where Adresse = 'BenArous' ");
                                    float ee=model->rowCount();
                                    model->setQuery("select * from Clients where Adresse = 'Ariana' ");
                                    float eee=model->rowCount();
                                    float total=e+ee+eee;
                                    QString a=QString("Tunis"+QString::number((e*100)/total,'f',2)+"%" );
                                    QString b=QString("BenArous"+QString::number((ee*100)/total,'f',2)+"%" );
                                    QString c=QString("Ariana"+QString::number((eee*100)/total,'f',2)+"%" );
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
                                    chart->setTitle("Pourcentage des adresses : nombre total : "+ QString::number(total));
                                    chart->legend()->hide();
                                    // Used to display the chart
                                    QChartView *chartView = new QChartView(chart);
                                    chartView->setRenderHint(QPainter::Antialiasing);
                                    chartView->resize(1000,500);
                                    chartView->show();
}


void MainWindow::on_tab_client_activated(const QModelIndex &index)
{
    QString val=ui->tab_client->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM Clients WHERE cin2='"+val+"' OR nom='"+val+"' OR prenom='"+val+"'");
    if (qry.exec())
    { while (qry.next())
        {
            //update
            //id
            ui->le_cin->setText(qry.value(0).toString());
            ui->le_nom->setText(qry.value(1).toString());
            ui->le_prenom->setText(qry.value(2).toString());
            ui->le_num->setText(qry.value(3).toString());

            //delete
            //id
            ui->le_cin->setText(qry.value(0).toString()); //pour supprimer


        }
    }
}

void MainWindow::on_tri_cin_clicked()
{
    Clients c1;
          ui->tab_client->setModel(c1.AfficherTriecin());
          bool test=c1.AfficherTrieNum();
          if (test)
             { QMessageBox::information(nullptr, QObject::tr("nice"),
                          QObject::tr("tri par num successful.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
              ui->tab_client->setModel(c1.AfficherTriecin());

          }


          else
             { QMessageBox::critical(nullptr, QObject::tr("not nice"),
                          QObject::tr("tri par num failed.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
          ui->tab_client->setModel(c1.AfficherTriecin());}
}
void MainWindow::on_tri_Nom_clicked()
{
    Clients c1;
          ui->tab_client->setModel(c1.AfficherTrieNom());
          bool test=c1.AfficherTrieNom();
          if (test)
             { QMessageBox::information(nullptr, QObject::tr("nice"),
                          QObject::tr("tri par num successful.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
              ui->tab_client->setModel(c1.AfficherTrieNom());

          }


          else
             { QMessageBox::critical(nullptr, QObject::tr("not nice"),
                          QObject::tr("tri par num failed.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
          ui->tab_client->setModel(c1.AfficherTrieNom());}
}
void MainWindow::on_photo_clicked()
{


        QString filename = QFileDialog::getSaveFileName(this,tr("choose"),"",tr("Image(*.png *.jpeg *.jpg *.bmp *.gif)"));
          QSqlQuery query;
                query.prepare("INSERT INTO IMAGE (IMG) "
                              "VALUES (:LOAD_FILE(filename))");
                query.bindValue(":LOAD_FILE(filename)",  filename);
                //QLabel* x = ui->imagee;
                //x->text();
                //x->(filename);

            if (QString::compare(filename,QString()) !=0)
           {
                QImage image;
                bool valid = image.load(filename);
                if(valid)
                {
                    image=image.scaledToWidth(ui->imagee->width(), Qt::SmoothTransformation);
                            ui->imagee->setPixmap(QPixmap::fromImage(image));
                            query.exec();
                }
                else
                {
                    //ERROR HANDLING
                }
            }
    }




void MainWindow::on_tri_2_clicked()
{
    Clients c1;
          ui->tab_client->setModel(c1.AfficherTrieNom());
          bool test=c1.AfficherTrieNom();
          if (test)
             { QMessageBox::information(nullptr, QObject::tr("nice"),
                          QObject::tr("tri par num successful.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
              ui->tab_client->setModel(c1.AfficherTrieNom());

          }


          else
             { QMessageBox::critical(nullptr, QObject::tr("not nice"),
                          QObject::tr("tri par num failed.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
          ui->tab_client->setModel(c1.AfficherTrieNom());}
}


void MainWindow::on_pushButton_3_clicked()
{
    QString account_sid = "ACd915f83d852c4ce543a4491b052f648a";
        QString auth_token = "e8409ed2cf020f5be8b87cbf0d36d688";
        QString from_number = "+16813293619"; // votre numéro Twilio
        QString to_number = "+21652633414"; // numéro de téléphone du destinataire
        QString message = "Hello dojdoj!"; // message à envoyer
        QString picture_url = ""; // URL de l'image, si vous voulez en envoyer une
        bool verbose = true; // afficher les messages de débogage ou non

        sendSMS(account_sid, auth_token, message, from_number, to_number, picture_url, verbose);

}

void MainWindow::sendSMS(QString account_sid, QString auth_token, QString message, QString from_number, QString to_number, QString picture_url, bool verbose)
{
    if (account_sid.isEmpty() || auth_token.isEmpty() || message.isEmpty() || from_number.isEmpty() || to_number.isEmpty()) {
           qDebug() << "You didn't include all necessary inputs!";
           qDebug() << "Call using -h for help.";
           return;
       }

       QUrl url("https://api.twilio.com/2010-04-01/Accounts/" + account_sid + "/Messages.json");
       QNetworkRequest request(url);
       QByteArray auth = QString("%1:%2").arg(account_sid, auth_token).toLocal8Bit().toBase64();
       request.setRawHeader("Authorization", "Basic " + auth);
       request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

       QUrlQuery params;
       params.addQueryItem("From", from_number);
       params.addQueryItem("To", to_number);
       params.addQueryItem("Body", message);
       if (!picture_url.isEmpty()) {
           params.addQueryItem("MediaUrl", picture_url);
       }

       QNetworkAccessManager *manager = new QNetworkAccessManager(this);
       QNetworkReply *reply = manager->post(request, params.toString(QUrl::FullyEncoded).toUtf8());

       QObject::connect(reply, &QNetworkReply::finished, [=](){
           QString response = QString(reply->readAll());
           if (reply->error() != QNetworkReply::NoError) {
               qDebug() << "Message send failed.";
               if (verbose && !response.isEmpty()) {
                   qDebug() << "Response:" << response;
               }
           } else {
               if (verbose) {
                   qDebug() << "SMS sent successfully!";
                   qDebug() << "Response:" << response;
               }
           }
           reply->deleteLater();
           manager->deleteLater();
       });

       QObject::connect(manager, &QNetworkAccessManager::authenticationRequired, [&](QNetworkReply *reply, QAuthenticator *authenticator){
           Q_UNUSED(reply);
           authenticator->setUser(account_sid);
           authenticator->setPassword(auth_token);
       });
}
void MainWindow::addGasState(){
    QSqlQuery qry,qry1;
    data = A.readFromArduino();
    QString DataAsString = QTextCodec::codecForMib(106)->toUnicode(data);
    qDebug() << DataAsString;
    qry.prepare("INSERT INTO DETECTIONFUMEE (INCENDIE,ETAT) "
                "VALUES (:INCENDIE, :ETAT)");
    qry.bindValue(":INCENDIE",DataAsString);
    qry.bindValue(":ETAT","0");
    qry.exec();
    qry1.prepare("update DETECTIONFUMEE set ETAT=:ETAT where INCENDIE>:INCENDIE");
    qry1.bindValue(":INCENDIE","200");
    qry1.bindValue(":ETAT","1");
    qry1.exec();


}

