#ifndef CLIENTMAINWINDOW_H
#define CLIENTMAINWINDOW_H

#include <QTcpSocket>
#include <QTimer>
#include <QWidget>
#include "structs.h"

namespace Ui {
class ClientMainWindow;
}

class ClientMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientMainWindow(QWidget *parent = nullptr);
    ~ClientMainWindow();

private:
    Ui::ClientMainWindow *ui;
    QTcpSocket *socket;
    QByteArray data;
    void sendToServer(User usr);
    QTimer timer;

public slots:
    void slotReadyRead();

private slots:
    void on_btConnect_clicked();
    void on_timer();
};

#endif // CLIENTMAINWINDOW_H
