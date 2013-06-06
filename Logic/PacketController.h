#pragma once
#include <QMutex>
#include "Packets.h"
#include "../Socket/TcpSocket.h"
#include "../Database/DataAccessObject.h"
#include "../Parser/ProtocolParser.h"
#include "../Database/DataAccessObject.h"

class PacketController
{
private:
    std::vector<ResponseGetRestaurantPacket> responsePacketRestaurant;
    std::vector<ResponseGetCommentsPacket> responsePacketComments;

	ProtocolParser* protocolParser;
	TcpSocket* sock;
	DataAccessObject* dataAccessObject;

    bool isTimeout;

    int packetIteratorRestaurant;
    int packetIteratorComments;

    int nextPacketToSend;

    QMutex mutex;
    QMutex mutexRestaurant;
    QMutex mutexComment;


	void addUserOption(int index);
	void checkRestaurantOption(int index);
	void getRestaurantOption(int index);
	void getCommentsOption(int index);
	void addCommentOption(int index);
	void addRestaurantOption(int index);
    void deleteCommentOption(int index);

    void sendNextPacket();

public:
    PacketController(TcpSocket* sock, DataAccessObject* dao);
	~PacketController(void);

	void service(AddUserPacket userPacket);
	void service(CheckRestaurantPacket packet);
	void service(GetRestaurantPacket packet);
	void service(GetCommentsPacket packet);
	void service(AddCommentPacket packet);
	void service(AddRestaurantPacket packet);
	void service(DeleteCommentPacket packet);
    void sendPing();

	void invokeService(char* input);

    bool getTimeout();

    void setTimeout();
};

