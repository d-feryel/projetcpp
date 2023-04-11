#include "socket.h"

socket::socket(qintptr handle,QObject *parent)
    :QTcpSocket(parent)
 {
     setSocketDescriptor(handle);
     connect(this,&socket::readyRead, [&]()
     {
         emit DuReadyRead(this);
     });
     connect(this ,&socket::stateChanged,[&](int S){
         emit DuStateChange(this,S);
     });
 }


