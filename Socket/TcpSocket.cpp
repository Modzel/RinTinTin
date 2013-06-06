#ifdef _WIN_32
    #pragma comment(lib,"Ws2_32.lib")
#endif

#include "TcpSocket.h"
#include <iostream>
#include <QString>
#include "../SendSocket.h"
#include <QThreadPool>

TcpSocket::TcpSocket(int port, int maxListeners) {
    this->sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    this->socketAdress.sin_family = AF_INET;
    this->socketAdress.sin_port = htons(port);
    this->socketAdress.sin_addr.s_addr = htonl(INADDR_ANY);
    this->maxSocketListeners = maxListeners;

    this->isTime = false;

    FD_ZERO(&(this->rfds));
    FD_SET(this->sock,&(this->rfds));
}

TcpSocket::TcpSocket(int port, int maxListeners,int time) {
#ifdef _WIN_32
	this->sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
#else
    this->sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
#endif
    this->socketAdress.sin_family = AF_INET;
    this->socketAdress.sin_port = htons(port);
    this->socketAdress.sin_addr.s_addr = htonl(INADDR_ANY);
	this->maxSocketListeners = maxListeners;

    this->isTime = true;
    this->time.tv_sec = time;
    this->time.tv_usec = 0;

    FD_ZERO(&(this->rfds));
    FD_SET(this->sock,&(this->rfds));
}

#ifdef _WIN_32
TcpSocket::TcpSocket(SOCKET socket) {
	this->sock = socket;
}
#else
TcpSocket::TcpSocket(int socket) {
   this->sock = socket;
}
#endif

TcpSocket::TcpSocket(void) {
}


TcpSocket::~TcpSocket(void) {
}

int TcpSocket::bindSocket() {
#ifdef _WIN_32
	if ( bind(this->sock, (sockaddr*)&(this->socketAdress), sizeof(this->socketAdress)) == SOCKET_ERROR ) {
        std::cout << "Wyst¹pil blad podczas bindowania adresu!\n";
		system("pause");
		return 1;
    }
#else
    if ( bind(this->sock, (struct sockaddr*)&(this->socketAdress), sizeof(this->socketAdress)) == -1) {
       std::cout << "Wystapil blad podczas bindowania adresu!\n";
       return 1;
    }

#endif

	return 0;
}

int TcpSocket::setSockOpt() {
#ifdef _WIN_32
#else
    int yep = 1;
    if( setsockopt(this->sock,SOL_SOCKET,SO_REUSEADDR, &yep ,sizeof(this->sock)) == -1) {
        std::cout<<"TERAZ TO JUZ MEGA BLAD!\n";
        return 1;
    }
#endif

    return 0;
}

int TcpSocket::listenSocket() {
#ifdef _WIN_32
	if( listen(this->sock, this->maxSocketListeners) == SOCKET_ERROR ) {
		std::cout << "Ustawienie gniazda w tryb nasluchiwania nie powiodlo sie\n";
		closesocket (sock);
		system("pause");
		return 1;
	}
#else
    if( listen(this->sock, this->maxSocketListeners) == -1 ) {
        std::cout << "Ustawienie gniazda w tryb nasluchiwania nie powiodlo sie\n";
        close (this->sock);
        return 1;
    }
#endif
	return 0;
}

#ifdef _WIN_32
SOCKET TcpSocket::acceptSocket() {
	return accept(this->sock,NULL,NULL);
}
#else
int TcpSocket::acceptSocket() {
    return accept(this->sock,0,0);
}

#endif

int TcpSocket::sendPackage(std::string message) {
    return send(this->sock, message.c_str(), message.length() + 1, 0);
}

int TcpSocket::sendPackage(QString message) {
    //Powinno dzialac na polskich znakach
    //return send(this->sock, message.toUtf8(), message.toUtf8().length() + 1, 0);
    //return write(this->sock, message.toUtf8(), message.toUtf8().length());

    SendSocket* messageThread = new SendSocket(this->sock, message.toUtf8(), message.toUtf8().length() + 1);

    QThreadPool::globalInstance()->start(messageThread);
}

bool TcpSocket::checkIfInvalid() {
#ifdef _WIN_32
	return this->sock == INVALID_SOCKET;
#else
    return this->sock == -1;
#endif
}

int TcpSocket::receivePackage(char* input, int size) {
    return recv(this->sock, input, size, 0);
    //return read(this->sock,input,size);

}

void TcpSocket::closeSocket() {
    close(this->sock);
}

int TcpSocket::selectSocket() {
    if(!isTime) {
        return select((this->sock)+1,&(this->rfds),NULL,NULL,NULL);
    } else {
        return select((this->sock)+1,&(this->rfds),NULL,NULL,&(this->time));
    }
}

void TcpSocket::set(int newTime) {
    this->time.tv_sec = newTime;

    FD_ZERO(&(this->rfds));
    FD_SET(this->sock,&(this->rfds));
}
