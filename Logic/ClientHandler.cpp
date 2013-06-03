#include "ClientHandler.h"
#include <iostream>
#ifdef _WIN_32
    #include <windows.h>
#endif
#include "../Parser/PacketType.h"
#include <QString>


ClientHandler::ClientHandler(TcpSocket* tcpsocket, QObject *parent) :
    QObject(parent)
{
    this->tcpsocket = tcpsocket;
    this->controller = new PacketController(tcpsocket);
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
    QString message = "01000\n";
    char *messageChar = "Helo Modzel!";
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

        std::cout<<inputBuffer;
        controller->invokeService(inputBuffer);

        memset(inputBuffer, ' ', 513);

    }
}

ClientHandler::~ClientHandler() {
    delete tcpsocket;
    delete controller;
}
