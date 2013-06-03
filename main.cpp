#ifdef _WIN_32
    #pragma comment(lib, "ws2_32.lib")
#endif

#include "Logic/Server.h"
#include <string>
#include <QTextCodec>
int port = 10001;

int main(int argc, char *argv[]) {
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QCoreApplication a(argc, argv);

    Server(port).start();
    return a.exec();
}
