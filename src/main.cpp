#include "readWriteLock.h"

#include <QApplication>
#pragma comment(lib, "user32.lib")

int main(int argc, char *argv[])
{
    qRegisterMetaType<std::queue<std::string>>("std::queue<std::string>");
    QApplication a(argc, argv);
    readWriteLock w;
    w.show();
    return a.exec();
}