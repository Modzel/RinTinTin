#include "ClientThread.h"
#include <iostream>

ClientThread::ClientThread() :
    QRunnable()
{
#ifdef _WIN_32
    this->tcpsocket = new TcpSocket(INVALID_SOCKET);
#else
    this->tcpsocket = new TcpSocket(-1);
#endif

    controller = NULL;
}

ClientThread::ClientThread(TcpSocket* tcpsocket,DataAccessObject* dao ) :
    QRunnable()
{
    this->tcpsocket = tcpsocket;
    this->controller = new PacketController(tcpsocket,dao);
}

void ClientThread::run() {
    char inputBuffer[513];
    int ret;
    int ret2;
    bool goOut = false;

    while (!goOut) {
            if((ret = this->tcpsocket->selectSocket()) > 0 ) {
                ret2 = this->tcpsocket->receivePackage(inputBuffer,513);
                if(ret2 == 0) {
                    goOut = true;
                    this->tcpsocket->closeSocket();
                    break;

                }
                std::cout<<"Niby nie";
                controller->invokeService(inputBuffer);

                memset(inputBuffer, ' ', 513);

             } else {
                if(ret == -1) {
                    std::cout<<"TUTAJ";
                    this->tcpsocket->closeSocket();
                    goOut = true;
                    break;
                } else {//ret == 0
                    //time(&timeout);
                    //controller->sendPing();
                    this->tcpsocket->closeSocket();
                    goOut = true;
                    break;

                }
            }
         //} else {
         //   time_t now = time(NULL);
         //   if(difftime(now,timeout) > 60)
         //       break;
        // }
    }

}

ClientThread::~ClientThread() {
    delete tcpsocket;
    delete controller;
}
