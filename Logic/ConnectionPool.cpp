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
	ClientHandler* addedClient = new ClientHandler(tcpsocket);
	clients.push_back(addedClient);
	std::cout<<"DODANO DZIFFFKO!";

	return addedClient;
}