#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "Logic/ClientHandler.h"
#include "Database/DataAccessObject.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(ClientHandler* client,DataAccessObject* dao,QObject *parent = 0);
    ~MyThread();
    
private:
    ClientHandler* client;
    DataAccessObject* dao;
signals:
    
public slots:
    
};

#endif // MYTHREAD_H
