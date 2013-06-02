#pragma once

#include <string>
#include <QString>

struct PingPacket {
	int userId;
};

struct PongPacket {
	int userId;
};

struct AddUserPacket {
    QString login;
    QString password;
};

struct ResponseAddUserPacket {
	int userId;
};

struct CheckRestaurantPacket {
	int localLastRestaurantId;
};

struct ResponseCheckRestaurantPacket {
	int globalLastRestaurantId;
     int globalRestaurantSize;
};

struct GetRestaurantPacket {
	int toUpdateRestaurantId;
};

struct ResponseGetRestaurantPacket {
	int restaurantId;
    QString restaurantName;
    QString restaurantAdress;
    QString restaurantType;
};

struct GetCommentsPacket {
	int restaurantId;
    int commentId;
    QString addedDate;
};

struct ResponseGetCommentsPacket {
    QString userLogin;
    QString text;
    QString date;
};

struct AddCommentPacket {
	int userId;
	int restaurantId;
    QString date;
    QString text;
};

struct ResponseAddCommentPacket {
	int commentId;
};

struct AddRestaurantPacket {
    QString restaurantName;
    QString restaurantAdress;
    QString restaurantType;
};

struct ResponseAddRestaurantPacket {
	int restaurantId;
};

struct DeleteCommentPacket {
	int commentId;
};

struct ReponseDeleteCommentPacket {
	bool ifDeleted;
};
