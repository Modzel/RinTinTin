#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "Logic/ClientHandler.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(ClientHandler* client,QObject *parent = 0);
    ~MyThread();
    
private:
    ClientHandler* client;
signals:
    
public slots:
    
};

#endif // MYTHREAD_H
