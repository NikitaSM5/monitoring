#include "servermainwindow.h"
#include "globaldata.h"
#include "ui_servermainwindow.h"

ServerMainWindow::ServerMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerMainWindow)
{
    ui->setupUi(this);
    GLOBAL->server.start();
    GLOBAL->active_users->show();
}

ServerMainWindow::~ServerMainWindow()
{
    delete ui;
}
