#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QRunnable>
#include "../Socket/TcpSocket.h"
#include "PacketController.h"

class ClientThread : public QRunnable
{

private:
    TcpSocket* tcpsocket;
    PacketController* controller;
public:
    explicit ClientThread();
    explicit ClientThread(TcpSocket* tcpsocket, DataAccessObject* dao );
    ~ClientThread();
    void run();
signals:
    
public slots:
    
};

#endif // CLIENTTHREAD_H
