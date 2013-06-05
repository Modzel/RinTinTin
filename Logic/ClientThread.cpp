#include "ClientThread.h"

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

    while (true) {
        //if(controller->getTimeout() == false) {
        std::cout<<"Niby jestem";
            if((ret = this->tcpsocket->selectSocket()) > 0 ) {
                this->tcpsocket->receivePackage(inputBuffer,513);

                std::cout<<"Niby nie";
                controller->invokeService(inputBuffer);

                memset(inputBuffer, ' ', 513);

             } else {
                    //time(&timeout);
                    controller->sendPing();

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
