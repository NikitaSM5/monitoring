#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server();
    QTcpSocket *socket;
    void start();
    QVector<QTcpSocket *> sockets;
    void sendToClient(QString, qintptr socket_descriptor);

private:
    QByteArray data;

public slots:
    void incomingConnection(qintptr socket_descriptor);
    void slotReadyRead();
    void removeUser(qintptr socket_descriptor);
};

#endif // SERVER_H
