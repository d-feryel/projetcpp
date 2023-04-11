#ifndef SOCKET_H
#define SOCKET_H
#include <QTcpSocket>

class socket : public QTcpSocket
{
     Q_OBJECT
public:
    socket(qintptr handle,QObject *parent);
signals:
    void DuReadyRead(socket * );
    void DuStateChange(socket * ,int );
};

#endif // SOCKET_H

