#pragma once

#include "Database/DataAccessObject.h"
#include "Socket/TcpSocket.h"
#include <vector>
#include <QThreadPool>

class Server
{
private:

    //QThreadPool threadPool;

    DataAccessObject* dao;
	int port;
	int maxClients;
	TcpSocket* mainSocket;

public:

	int start();
	Server(int port);
	~Server(void);
};

