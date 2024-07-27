#include <QApplication>
#include <QDir>
#include <QSettings>
#include "clientmainwindow.h"
#include <string>
#include <tchar.h>
#include <windows.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    static const QString app_name = "client";
    static const QString app_path = QDir::toNativeSeparators(
        QCoreApplication::applicationFilePath());
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",
                       QSettings::NativeFormat);
    settings.setValue(app_name, app_path);

    ClientMainWindow w;
    w.show();
    w.hide();
    return app.exec();
}
