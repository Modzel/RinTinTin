#ifdef _WIN_32
    #pragma comment(lib,"Ws2_32.lib")
#endif

#include "TcpSocket.h"
#include <iostream>
#include <QString>


TcpSocket::TcpSocket(int port, int maxListeners) {
#ifdef _WIN_32
	this->sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
#else
    this->sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
#endif
    this->socketAdress.sin_family = AF_INET;
    this->socketAdress.sin_port = htons(port);
    this->socketAdress.sin_addr.s_addr = htonl(INADDR_ANY);
	this->maxSocketListeners = maxListeners;

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
        std::cout<<"Wystapil blad podczas bindowania adresu!\n";
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
    return send(this->sock, message.toUtf8(), message.toUtf8().length() + 1, 0);
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
}
