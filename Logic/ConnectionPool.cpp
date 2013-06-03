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


    return new ClientHandler();
}

void ConnectionPool::deleteClient(ClientHandler* client) {
}
