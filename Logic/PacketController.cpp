#include "PacketController.h"
#include "../Exceptions/BadPackageException.h"
#include <iostream>
#include <vector>
#include <QDebug>


PacketController::PacketController(TcpSocket* sock) {
	this->sock = sock;
	this->dataAccessObject = new DataAccessObject();
	this->protocolParser = new ProtocolParser();
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
    std::vector<ResponseGetRestaurantPacket> responsePacket;
	char inputBuffor[512];

    responsePacket = dataAccessObject->getRestaurant(packet);
    for(unsigned int i = 0; i < responsePacket.size(); ++i) {
        sock->sendPackage(protocolParser->parsePacketOut(responsePacket[i]));
        sock->receivePackage(inputBuffor,513);
        try{
            if( protocolParser->parseNextData(inputBuffor) == true )
                continue;
        } catch(BadPackageException* exception) {
            exception->send();
            delete exception;
            return;
        }
	}

    sock->sendPackage(protocolParser->parsePacketEndOfData());
}

void PacketController::service(GetCommentsPacket packet) {
    std::vector<ResponseGetCommentsPacket> responsePacket;
	char inputBuffor[512];

    responsePacket = dataAccessObject->getComment(packet);
    for(unsigned int i = 0; i < responsePacket.size(); ++i) {
        sock->sendPackage(protocolParser->parsePacketOut(responsePacket[i]));
        sock->receivePackage(inputBuffor,513);
        try{
            if( protocolParser->parseNextData(inputBuffor) == true )
                continue;
        } catch(BadPackageException* exception) {
            exception->send();
            delete exception;
            return;
        }
    }

    sock->sendPackage(protocolParser->parsePacketEndOfData());
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
		//NARAZIE ZOSTAWIAMY
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
	default:
        qDebug()<<"DZIIIIWNE TOOOO\n";
		break;
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
