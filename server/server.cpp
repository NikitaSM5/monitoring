#include "server.h"
#include <QDataStream>
#include "globaldata.h"
#include <structs.h>

Server::Server()
{

}

void Server::sendToClient(QString str, qintptr socket_descriptor)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << str;
    for (auto &i : sockets)
        if (i->socketDescriptor() == socket_descriptor)
            i->write(data);
}

void Server::start()
{
    if (this->listen(QHostAddress::Any, 2323))
        qDebug() << "Start";
}

void Server::incomingConnection(qintptr socket_descriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socket_descriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    sockets.push_back(socket);
    qDebug() << "connected " << socket_descriptor;
}

void Server::slotReadyRead()
{
    socket = (QTcpSocket *) sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);
    if (in.status() == QDataStream::Ok) {
        QString str;
        in >> str;

        if (str == "user") {
            User usr;
            in >> usr;
            usr.domain = QString::number(socket->socketDescriptor());
            GLOBAL->active_users->addNewUser(usr);
        }
        if (str == "screenshot") {
            QByteArray data;
            in >> data;
            qDebug() << "Screenshot saved";
        }

    } else
        qDebug() << "Unable to read";
}
