#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>

class socketmes;
class server : public QTcpServer
{
public:
   server(QObject *parent = nullptr);
    bool startServer(quint16 port );
protected:
    void incomingConnection(qintptr handle);
private:
    QList< socketmes *>mSockets;
};

#endif // SERVER_H





