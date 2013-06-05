#pragma once

#ifdef _WIN_32
    #include <winsock2.h>
#else
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <netdb.h>
    #include <netinet/in.h>
    #include <sys/select.h>
    #include <sys/time.h>
#endif
#include <string>
#include <QString>

/**
	Klasa tworzaca gniazdo i zarzadzajaca nim
*/
class TcpSocket {
private:
	friend class ClientHandler;
#ifdef _WIN_32
	SOCKET sock;
	SOCKADDR_IN socketAdress;
#else
    int sock;
    struct sockaddr_in socketAdress;

    struct timeval time;
    fd_set rfds;

#endif

	int maxSocketListeners;

	

public:
    TcpSocket(int port, int maxListeners, int time);
	TcpSocket();
	~TcpSocket(void);

#ifdef _WIN_32
	TcpSocket(SOCKET socket);
#else
    TcpSocket(int sock);
#endif

	int bindSocket();
	int listenSocket();
	bool checkIfInvalid();
    void closeSocket();
    int setSockOpt();
    int selectSocket();

#ifdef _WIN_32
	SOCKET acceptSocket();
#else
    int acceptSocket();
#endif

	int receivePackage(char* input, int size);

	int sendPackage(std::string message);
    int sendPackage(QString message);
};

