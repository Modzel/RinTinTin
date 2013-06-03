#pragma once

#include "Database/DataAccessObject.h"
#include "Socket/TcpSocket.h"
#include <vector>

class Server
{
private:

    DataAccessObject* dao;
	int port;
	int maxClients;
	TcpSocket* mainSocket;

public:

	int start();
	Server(int port);
	~Server(void);
};

