#include "server.h"
#include "socketmes.h"
#include <QTextStream>
#include <QDebug>


server::server(QObject *parent )
   :QTcpServer(parent)
{
}
bool server::startServer(quint16 port){
     return listen(QHostAddress::Any,port);
}
void server::incomingConnection(qintptr handle)
{
     qDebug() << "employee connecter with handle:" << handle ;
    auto socket = new socketmes(handle,this);
    mSockets << socket;

    for(auto i :mSockets){
        QTextStream T(i);
       T << "server:s'est connecté:"  <<handle;
       i->flush();
    }


    connect(socket ,&socketmes::DuReadyRead, [&](socketmes * S)
    {
        qDebug() <<"DuReadyRead" ;
        QTextStream T(S);
        auto text = T.readAll();
        for (auto i : mSockets){
             QTextStream K(i);
             K << text ;
                i->flush();
        }
    });
    connect(socket, &socketmes::DuStateChange, [&](socketmes * S,int ST){
         qDebug() << "DuStateChange  with handle:"
                  <<  S->socketDescriptor()  ;
        if (ST == QTcpSocket ::UnconnectedState){
            qDebug() << "UnconnectedState with handle:"
                     << S->socketDescriptor() ;
            mSockets.removeOne(S);
            for(auto i : mSockets){
                QTextStream K(i);
                K << "Server: ELcliente"
                  << S->socketDescriptor()
                  <<"server:s'est deconnecté:";
                i->flush();
            }
        }
    });
}
