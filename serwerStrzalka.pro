#-------------------------------------------------
#
# Project created by QtCreator 2013-06-01T18:37:26
#
#-------------------------------------------------

QT       += core
QT       += sql
QT       -= gui

TARGET = serwerStrzalka
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Database/DataAccessObject.cpp \
    Exceptions/Exception.cpp \
    Exceptions/BadPackageException.cpp \
    Logic/Server.cpp \
    Logic/PacketController.cpp \
    Parser/ProtocolParser.cpp \
    Socket/TcpSocket.cpp \
    Logic/ClientThread.cpp \
    SendSocket.cpp

HEADERS += \
    Database/DataAccessObject.h \
    Exceptions/Exception.h \
    Exceptions/BadPackageException.h \
    Logic/Server.h \
    Logic/Packets.h \
    Logic/PacketController.h \
    Parser/ProtocolParser.h \
    Parser/PacketType.h \
    Socket/TcpSocket.h \
    Logic/ClientThread.h \
    SendSocket.h
