#include "socketmes.h"

Socketmes::Socketmes(qintptr handle,QObject *parent)
    :QTcpSocket(parent)
 {
     setSocketDescriptor(handle);
     connect(this,&Socketmes::readyRead, [&]()
     {
         emit DuReadyRead(this);
     });
     connect(this ,&Socketmes::stateChanged,[&](int S){
         emit DuStateChange(this,S);
     });
 }



