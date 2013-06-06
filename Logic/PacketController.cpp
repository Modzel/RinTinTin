#include "PacketController.h"
#include "../Exceptions/BadPackageException.h"
#include <iostream>
#include <vector>
#include <QDebug>


PacketController::PacketController(TcpSocket* sock, DataAccessObject* dao) {
	this->sock = sock;
    this->dataAccessObject = dao;
	this->protocolParser = new ProtocolParser();
    this->isTimeout = false;
}


PacketController::~PacketController(void) {
	delete dataAccessObject;
	delete protocolParser;
}

void PacketController::service(AddUserPacket userPacket) {
    ResponseAddUserPacket responsePacket = dataAccessObject->addUser(userPacket);

	sock->sendPackage(protocolParser->parsePacketOut(responsePacket));

}

void PacketController::service(CheckRestaurantPacket packet) {
    ResponseCheckRestaurantPacket responsePacket = dataAccessObject->findNewestRestaurant();

	sock->sendPackage(protocolParser->parsePacketOut(responsePacket));
}

void PacketController::service(GetRestaurantPacket packet) {

    this->nextPacketToSend = 6;

    responsePacketRestaurant = dataAccessObject->getRestaurant(packet);

    packetIteratorRestaurant = 0;
    if (packetIteratorRestaurant < responsePacketRestaurant.size() ) {
        sock->sendPackage(protocolParser->parsePacketOut(responsePacketRestaurant[packetIteratorRestaurant]));
        ++packetIteratorRestaurant;
    }
    else {
        for(int i = 0; i < 2; ++i) {
            sock->sendPackage(protocolParser->parsePacketEndOfData());
        }
    }

}

void PacketController::service(GetCommentsPacket packet) {

    this->nextPacketToSend = 10;

    responsePacketComments = dataAccessObject->getComment(packet);
    packetIteratorComments = 0;
    if (packetIteratorComments < responsePacketComments.size() ) {
        sock->sendPackage(protocolParser->parsePacketOut(responsePacketComments[packetIteratorComments]));
        ++packetIteratorComments;
    }
    else {
        sock->sendPackage(protocolParser->parsePacketEndOfData());
    }
}

void PacketController::service(AddCommentPacket packet) {
    ResponseAddCommentPacket responsePacket = dataAccessObject->addComment(packet);

	sock->sendPackage(protocolParser->parsePacketOut(responsePacket));
}
void PacketController::service(AddRestaurantPacket packet) {
    ResponseAddRestaurantPacket responsePacket = dataAccessObject->addRestaurant(packet);

	sock->sendPackage(protocolParser->parsePacketOut(responsePacket));
}
void PacketController::service(DeleteCommentPacket packet) {
    ReponseDeleteCommentPacket responsePacket = dataAccessObject->deleteComment(packet);

	sock->sendPackage(protocolParser->parsePacketOut(responsePacket));
}

void PacketController::invokeService(char *inputBuffer) {
	int index = 0;	
	PacketType type;
	try { 
		type = protocolParser->parsePacketIn(inputBuffer,index);
	} catch(BadPackageException* exception) {
		exception->send();
		delete exception;
		return;
	}

	switch (type)
	{
    case PONG:
        qDebug()<<"Przychodzacy pakiet PONG";
        this->isTimeout = false;
        break;
	case ADD_USER:
        qDebug()<<"Przychodzacy pakiet ADD_USER";
		this->addUserOption(index);
		break;
	case CHECK_RESTAURANT:
        qDebug()<<"Przychodzacy pakiet CHECK_RESTAURANT\n";
		this->checkRestaurantOption(index);
		break;
	case GET_RESTAURANT:
        qDebug()<<"Przychodzacy pakiet GET_RESTAURANT\n";
		this->getRestaurantOption(index);
		break;
	case GET_COMMENTS:
        qDebug()<<"Przychodzacy pakiet GET_COMMENTS\n";
		this->getCommentsOption(index);
		break;
	case ADD_COMMENT:
        qDebug()<<"Przychodzacy pakiet ADD_COMMENT\n";
		this->addCommentOption(index);
		break;
	case ADD_RESTAURANT:
        qDebug()<<"Przychodzacy pakiet ADD_RESTAURANT\n";
		this->addRestaurantOption(index);
		break;
	case DELETE_COMMENT:
        qDebug()<<"Przychodzacy pakiet DELETE_COMMENT\n";
		this->deleteCommentOption(index);
		break;
    case SEND_NEXT:
        qDebug()<<"Przychodzacy pakiet NEXT_SEND\n";
        this->sendNextPacket();
        break;
	default:
        qDebug()<<"DZIWNE TO";
		break;
	}
}

void PacketController::sendNextPacket() {
    if(this->nextPacketToSend == 6) {
        //RESTAURANT
        std::cout<<"WIELKOSC TABLICY: "<<this->responsePacketRestaurant.size()<<"Iterator: "<<packetIteratorRestaurant<<std::endl;
        if(this->packetIteratorRestaurant < this->responsePacketRestaurant.size()) {

            sock->sendPackage(protocolParser->parsePacketOut(responsePacketRestaurant[packetIteratorRestaurant]));
            ++packetIteratorRestaurant;
         } else {
            sock->sendPackage(protocolParser->parsePacketEndOfData());
            packetIteratorRestaurant = 0;
        }

    } else {//this->nextPacketToSend == 10
        //COMMENTS
        std::cout<<"WIELKOSC TABLICY: "<<this->responsePacketComments.size()<<"Iterator: "<<packetIteratorComments<<std::endl;
        if(this->packetIteratorComments < this->responsePacketComments.size()) {
            sock->sendPackage(protocolParser->parsePacketOut(this->responsePacketComments[packetIteratorComments]));
            ++packetIteratorComments;
        } else {
            sock->sendPackage(protocolParser->parsePacketEndOfData());
            packetIteratorComments = 0;

        }
    }
}

void PacketController::addUserOption(int index) {
	AddUserPacket packet;
	try {
		packet = protocolParser->parseUserPacket(index);
	} catch(BadPackageException* exception) {
		exception->send();
		delete exception;
		return;
	}

	this->service(packet);
}


void PacketController::checkRestaurantOption(int index) {
	CheckRestaurantPacket packet;
	try {
		packet = protocolParser->parseCheckRestaurantPacket(index);
	} catch(BadPackageException* exception) {
		exception->send();
		delete exception;
		return;
	}

	this->service(packet);
}

void PacketController::getRestaurantOption(int index) {
	GetRestaurantPacket packet;
	try {
		packet = protocolParser->parseGetRestaurantPacket(index);
	} catch(BadPackageException* exception) {
		exception->send();
		delete exception;
		return;
	}

	this->service(packet);
}

void PacketController::getCommentsOption(int index) {
	GetCommentsPacket packet;
	try {
		packet = protocolParser->parseGetCommentsPacket(index);
	} catch(BadPackageException* exception) {
		exception->send();
		delete exception;
		return;
	}

	this->service(packet);
}

void PacketController::addCommentOption(int index) {
	AddCommentPacket packet;
	try {
		packet = protocolParser->parseAddCommentPacket(index);
	} catch(BadPackageException* exception) {
		exception->send();
		delete exception;
		return;
	}

	this->service(packet);
}

void PacketController::addRestaurantOption(int index) {
	AddRestaurantPacket packet;
	try {
		packet = protocolParser->parseAddRestaurantPacket(index);
	} catch(BadPackageException* exception) {
		exception->send();
		delete exception;
		return;
	}

	this->service(packet);
}

void PacketController::deleteCommentOption(int index) {
	DeleteCommentPacket packet;
	try {
		packet = protocolParser->parseDeleteCommentPacket(index);
	} catch(BadPackageException* exception) {
		exception->send();
		delete exception;
		return;
	}

	this->service(packet);
}

void PacketController::sendPing() {
    sock->sendPackage(this->protocolParser->parsePingPacket());
}

bool PacketController::getTimeout() {
    return this->isTimeout;
}

void PacketController::setTimeout() {
    this->isTimeout = true;
}
