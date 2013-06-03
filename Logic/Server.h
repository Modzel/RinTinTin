#pragma once

#include "ConnectionPool.h"
#include <vector>

class Server
{
private:



	ConnectionPool* connectionPool;
	int port;
	int maxClients;
	TcpSocket* mainSocket;

public:

	int start();
	Server(int port);
	~Server(void);
};

