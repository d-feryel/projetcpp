#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "dumessengerserver.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    bool test=c.createconnect();
     MainWindow w;
     QWidget wa;
    if(test)
    {wa.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    DuMessengerServer Server;
   if(!Server.startServer(3333)){
        qDebug() << "Error:" << Server.errorString();
        return 1;
   }
    qDebug() << "Server started ...";
    return a.exec();


    return a.exec();
}
