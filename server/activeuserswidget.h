#ifndef ACTIVEUSERSWIDGET_H
#define ACTIVEUSERSWIDGET_H

#include <QWidget>
#include "qtreewidget.h"
#include "structs.h"

enum TypeColumn {
    tcDomain,
    tcMachine,
    tcIp,
    tcUser,
    tcLastActiveTime,
};

namespace Ui {
class ActiveUsersWidget;
}

class ActiveUsersWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ActiveUsersWidget(QWidget *parent = nullptr);
    ~ActiveUsersWidget();
    void addNewUser(User usr);
    void removeUser(qintptr socket_descriptor);

private slots:
    void on_treeClients_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::ActiveUsersWidget *ui;
};

#endif // ACTIVEUSERSWIDGET_H
