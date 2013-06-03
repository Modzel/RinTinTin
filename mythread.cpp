#include "mythread.h"

MyThread::MyThread(ClientHandler* client,DataAccessObject* dao, QObject *parent) :
    QThread(parent)
{
    this->client = client;
    this->dao = new DataAccessObject();

}

MyThread::~MyThread() {

    delete client;
    delete dao;
}
