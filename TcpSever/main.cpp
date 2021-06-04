#include "tcpsever.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpSever w;
    w.show();
    return a.exec();
}
