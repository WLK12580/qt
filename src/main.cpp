#include "qserialPort.h"

#include <QApplication>
#pragma comment(lib, "user32.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qserialPort w;
    w.show();
    return a.exec();
}