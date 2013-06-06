#include "SendSocket.h"
#include <iostream>

SendSocket::SendSocket(int sock, QByteArray inputBuffer, int size) : QRunnable()
{
    this->inputBuffer = inputBuffer;
    this->size = size;
    this->sock = sock;
}


void SendSocket::run() {
    send(this->sock,inputBuffer,size,0);
}
