#pragma once
#include "Packets.h"
#include "../Socket/TcpSocket.h"
#include "../Database/DataAccessObject.h"
#include "../Parser/ProtocolParser.h"

class PacketController
{
private:
	ProtocolParser* protocolParser;
	TcpSocket* sock;
	DataAccessObject* dataAccessObject;

	void addUserOption(int index);
	void checkRestaurantOption(int index);
	void getRestaurantOption(int index);
	void getCommentsOption(int index);
	void addCommentOption(int index);
	void addRestaurantOption(int index);
	void deleteCommentOption(int index);

public:
	PacketController(TcpSocket* sock);
	~PacketController(void);

	void service(AddUserPacket userPacket);
	void service(CheckRestaurantPacket packet);
	void service(GetRestaurantPacket packet);
	void service(GetCommentsPacket packet);
	void service(AddCommentPacket packet);
	void service(AddRestaurantPacket packet);
	void service(DeleteCommentPacket packet);

	void invokeService(char* input);
};

