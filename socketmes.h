#ifndef SOCKETMES_H
#define SOCKETMES_H
#include <QTcpSocket>

class Socketmes : public QTcpSocket
{
     Q_OBJECT
public:
    Socketmes(qintptr handle,QObject *parent);
signals:
    void DuReadyRead(Socketmes * );
    void DuStateChange(Socketmes * ,int );
};

#endif // SOCKETMES_H


