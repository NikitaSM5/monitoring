#ifndef SERVERMAINWINDOW_H
#define SERVERMAINWINDOW_H

#include <QWidget>

namespace Ui {
class ServerMainWindow;
}

class ServerMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ServerMainWindow(QWidget *parent = nullptr);
    ~ServerMainWindow();

private:
    Ui::ServerMainWindow *ui;
};

#endif // SERVERMAINWINDOW_H
