#ifndef DUMESSENGERSOCKET_H
#define DUMESSENGERSOCKET_H
#include <QTcpSocket>

class DuMessengerSocket : public QTcpSocket
{
    Q_OBJECT
public:
    DuMessengerSocket( qintptr handle,QObject *parent);
signals:
    void DuReadyRead(DuMessengerSocket * );
    void DuStateChange(DuMessengerSocket * ,int );
};
 // end namespace DuarteCorporation
#endif // DUMESSENGERSOCKET_H

