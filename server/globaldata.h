#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QTime>
#include "activeuserswidget.h"
#include "qobject.h"
#include "server.h"

#define GLOBAL (GlobalData::instance())

class GlobalData : public QObject
{
    Q_OBJECT

public:
    static GlobalData *instance();
    Server server;
    ActiveUsersWidget *active_users = new ActiveUsersWidget;

private:
    GlobalData();
    ~GlobalData();

private:
};

#endif // GLOBALDATA_H
