#pragma once

#include "PacketType.h"
#include "../Logic/Packets.h"
#include <QString>

class ProtocolParser
{
private:
	friend class PacketController;

	char* data;

	////////////////////////////////////////////////////////////IN//////////////////////////////////////////////////////////////////////
	PacketType readPacketType(int& index);

	AddUserPacket parseUserPacket(int index);

	CheckRestaurantPacket parseCheckRestaurantPacket(int index);

	GetRestaurantPacket parseGetRestaurantPacket(int index);

	GetCommentsPacket parseGetCommentsPacket(int index);

	AddCommentPacket parseAddCommentPacket(int index);

	AddRestaurantPacket parseAddRestaurantPacket(int index);

	DeleteCommentPacket parseDeleteCommentPacket(int index);


	bool parseNextData(char* inputBuffor);
	/////////////////////////////////////////////////////////////////OUT/////////////////////////////////////////////////////////////////////

    QString parsePacketOut(ResponseAddCommentPacket);
    QString parsePacketOut(ResponseAddRestaurantPacket);
    QString parsePacketOut(ResponseAddUserPacket);
    QString parsePacketOut(ResponseCheckRestaurantPacket);
    QString parsePacketOut(ResponseGetCommentsPacket);
    QString parsePacketOut(ResponseGetRestaurantPacket);
    QString parsePacketOut(PongPacket);
    QString parsePacketOut(ReponseDeleteCommentPacket);
    QString parsePacketOut(PingPacket packet);
    QString parsePacketEndOfData();
    QString parsePingPacket();

    ////////////////////////////////////////////////////////////////////////////////////////////////

    void deencryption(char* data);
    void encryption(QString& data);
public:
	ProtocolParser(void);
	~ProtocolParser(void);
	PacketType parsePacketIn(char* data,int& index);
};

