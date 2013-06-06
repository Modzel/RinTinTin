#ifdef _WIN_32
    #pragma comment(lib, "ws2_32.lib")
#endif

#include "Logic/Server.h"
#include <string>
#include <QTextCodec>
int port = 10001;
int maxUsers = 1024;

int main(int argc, char *argv[]) {

    QCoreApplication a(argc, argv);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QThreadPool::globalInstance()->setMaxThreadCount(maxUsers);

    //if(argv[1] == NULL){
        Server(port).start();
    //} else {
    //    Server(atoi(argv[1])).start();
    //}
    return a.exec();
}
