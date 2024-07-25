#include <QApplication>
#include "clientmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ClientMainWindow w;
    w.show();
    return app.exec();
}
