
#include <QApplication>
#include "servermainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ServerMainWindow w;
    w.show();
    return app.exec();
}
