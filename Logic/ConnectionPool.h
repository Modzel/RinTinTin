#pragma once
#include <vector>
#include "ClientHandler.h"
#include "../Socket/TcpSocket.h"
#include <QThread>

class ConnectionPool
{
private: 
    std::vector<ClientHandler*> clients;
public:
	ConnectionPool(void);
	~ConnectionPool(void);
	bool checkIfInvalid(int i);
    int findFreeSocket();
    ClientHandler* addClient(TcpSocket* tcpsocket);
    void deleteClient(ClientHandler* client);
};

