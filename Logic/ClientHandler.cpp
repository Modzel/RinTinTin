#include "ClientHandler.h"
#include <iostream>
#ifdef _WIN_32
    #include <windows.h>
#endif
#include "../Parser/PacketType.h"
#include <QString>


ClientHandler::ClientHandler(TcpSocket* tcpsocket,DataAccessObject* dao, QObject *parent ) :
    QObject(parent)
{
    this->tcpsocket = tcpsocket;
    this->controller = new PacketController(tcpsocket,dao);
}

ClientHandler::ClientHandler(QObject *parent) :
    QObject(parent)
{
#ifdef _WIN_32
    this->tcpsocket = new TcpSocket(INVALID_SOCKET);
#else
    this->tcpsocket = new TcpSocket(-1);
#endif

    controller = NULL;
}



void ClientHandler::doSetup(QThread &cThread){
    connect(&cThread,SIGNAL(started()),this,SLOT(doWork()));
}

void ClientHandler::doWork() {
    char inputBuffer[513];
    int ret;
    while (true) {
        ret = this->tcpsocket->receivePackage(inputBuffer,513);
        if (ret == 0) {
            std::cout<<"Polaczenie zamkniete !\n";
            break;

#ifdef _WIN_32
        } else if ( ret == SOCKET_ERROR ) {
#else
        } else if ( ret == -1 ) {
#endif
            break;
        }

        controller->invokeService(inputBuffer);

        memset(inputBuffer, ' ', 513);

    }
}

ClientHandler::~ClientHandler() {
    delete tcpsocket;
    delete controller;
}
