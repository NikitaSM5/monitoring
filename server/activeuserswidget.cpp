#include "activeuserswidget.h"
#include "globaldata.h"
#include "ui_activeuserswidget.h"

ActiveUsersWidget::ActiveUsersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActiveUsersWidget)
{
    ui->setupUi(this);
}

ActiveUsersWidget::~ActiveUsersWidget()
{
    delete ui;
}

void ActiveUsersWidget::addNewUser(User usr)
{
    for (int i = 0; i < ui->treeClients->topLevelItemCount(); i++) {
        if (usr.domain == ui->treeClients->topLevelItem(i)->text(tcDomain)) {
            QTreeWidgetItem *itm = ui->treeClients->takeTopLevelItem(i);
            itm->setText(tcDomain, usr.domain);
            itm->setText(tcIp, usr.ip);
            itm->setText(tcLastActiveTime, usr.last_active_time);
            itm->setText(tcMachine, usr.machine);
            itm->setText(tcUser, usr.user);
        }
    }

    QTreeWidgetItem *itm = new QTreeWidgetItem;
    itm->setText(tcDomain, usr.domain);
    itm->setText(tcIp, usr.ip);
    itm->setText(tcLastActiveTime, usr.last_active_time);
    itm->setText(tcMachine, usr.machine);
    itm->setText(tcUser, usr.user);

    ui->treeClients->addTopLevelItem(itm);

    for (int i : {tcDomain, tcIp, tcLastActiveTime, tcMachine, tcUser})
        ui->treeClients->resizeColumnToContents(i);
}

void ActiveUsersWidget::removeUser(qintptr socket_descriptor)
{
    for (int i = 0; i < ui->treeClients->topLevelItemCount(); i++)
        if (ui->treeClients->topLevelItem(i)->text(tcDomain).toInt() == socket_descriptor)
            ui->treeClients->takeTopLevelItem(i);
}

void ActiveUsersWidget::on_treeClients_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    GLOBAL->server.sendToClient("screenshot", item->text(tcDomain).toInt());
}
