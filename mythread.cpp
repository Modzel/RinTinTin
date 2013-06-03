#include "mythread.h"

MyThread::MyThread(ClientHandler* client, QObject *parent ) :
    QThread(parent)
{
    this->client = client;

}

MyThread::~MyThread() {

    delete client;
}
