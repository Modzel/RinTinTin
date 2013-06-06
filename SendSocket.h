#ifndef SENDSOCKET_H
#define SENDSOCKET_H

#include <QRunnable>
#include <QByteArray>
#include <sys/socket.h>
#include <sys/types.h>

class SendSocket : public QRunnable
{
private:
    int sock;
    QByteArray inputBuffer;
    int size;
public:
    SendSocket(int sock, QByteArray inputBuffer, int size);

    void run();
};

#endif // SENDSOCKET_H
