#pragma comment(lib, "ws2_32.lib")

#include "Server.h"
#ifdef _WIN_32
    #include <winsock2.h>
    #include <windows.h>
#else
    #include <sys/socket.h>
#endif

#include <iostream>
#include <string>
#include <QThread>
#include <QObject>
#include <QDebug>
#include "../Socket/TcpSocket.h"

Server::Server(int port) {

qDebug()<< "dupa";	
this->port = port;
	this->maxClients = 1024;
	this->connectionPool = new ConnectionPool();
}


Server::~Server(void)
{
	delete connectionPool;
}



int Server::start() {
    #ifdef _WIN_32
        WSADATA wsaData;
        if( WSAStartup( MAKEWORD(2,2), &wsaData ) != 0 ) {

		std::cout<<"Wystapil blad z zainicjowaniem biblioteki!\n";
		return -1;
	}
    #endif
	mainSocket = new TcpSocket(this->port,20);
	if (mainSocket->bindSocket() == 1) return 1;
	if (mainSocket->listenSocket() == 1) return 1;
	TcpSocket* clientSocket;
	while (true) {
		clientSocket = new TcpSocket(mainSocket->acceptSocket());
		if( !clientSocket->checkIfInvalid() ) {

			ClientHandler* client = connectionPool->addClient(clientSocket);

            QThread thread;

            client->doSetup(thread);
            client->moveToThread(&thread);

            thread.start();
		}

	}	
	//reszta, obaczymy co tutaj bedzie
    #ifdef _WIN_32
        WSACleanup();
        system("pause");
    #endif
	return 0;
}
