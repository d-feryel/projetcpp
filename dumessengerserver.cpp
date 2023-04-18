#include "dumessengerserver.h"
#include "DuMessengerSocket.h"
#include <QTextStream>
#include <QDebug>


DuMessengerServer::DuMessengerServer(QObject *parent )
   :QTcpServer(parent)
{
}
bool DuMessengerServer::startServer(quint16 port){
     return listen(QHostAddress::Any,port);
}
void DuMessengerServer::incomingConnection(qintptr handle)
{
     qDebug() << "employee connecter with handle:" << handle ;
    auto socket = new DuMessengerSocket(handle,this);
    mSockets << socket;

    for(auto i :mSockets){
        QTextStream T(i);
       T << "server:s'est connectee:"  <<handle;
       i->flush();
    }


    connect(socket ,&DuMessengerSocket::DuReadyRead, [&](DuMessengerSocket * S)
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
    connect(socket, &DuMessengerSocket::DuStateChange, [&](DuMessengerSocket * S,int ST){
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
//end namespace DuarteCorporation
