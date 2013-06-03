#pragma once

#include "ConnectionPool.h"
#include "Database/DataAccessObject.h"s
#include <vector>

class Server
{
private:



	ConnectionPool* connectionPool;
    DataAccessObject* dao;
	int port;
	int maxClients;
	TcpSocket* mainSocket;

public:

	int start();
	Server(int port);
	~Server(void);
};

