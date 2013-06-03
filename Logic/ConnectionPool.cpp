#include "ConnectionPool.h"
#include<iostream>


ConnectionPool::ConnectionPool(void){
	
}


ConnectionPool::~ConnectionPool(void){

}

bool ConnectionPool::checkIfInvalid(int i) {
	return this->clients[i]->tcpsocket->checkIfInvalid();
}

ClientHandler* ConnectionPool::addClient(TcpSocket* tcpsocket) {
    ClientHandler* addClient = new ClientHandler(tcpsocket);

    clients.push_back(addClient);
	std::cout<<"DODANO DZIFFFKO!";

    return addClient;
}

void ConnectionPool::deleteClient(ClientHandler* client) {
}
