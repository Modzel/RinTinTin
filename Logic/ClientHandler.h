#ifndef CLIENTHANDLERV_H
#define CLIENTHANDLERV_H

#include <QObject>
#include <QThread>

#include "../Socket/TcpSocket.h"
#include "../Logic/PacketController.h"
#include "Database/DataAccessObject.h"

class ClientHandler : public QObject
{
    Q_OBJECT
private:
    friend class ConnectionPool;
    TcpSocket* tcpsocket;
    PacketController* controller;
public:
    explicit ClientHandler(QObject *parent = 0);
    explicit ClientHandler(TcpSocket* tcpsocket, DataAccessObject* dao, QObject *parent = 0);

    ~ClientHandler();
    void doSetup(QThread &cThread);
signals:
    
public slots:
    void doWork();
};

#endif // CLIENTHANDLERV_H
