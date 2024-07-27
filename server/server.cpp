#include "server.h"
#include <QDataStream>
#include <QFile>
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
    connect(socket, &QTcpSocket::disconnected, this, [this, socket_descriptor]() {
        GLOBAL->active_users->removeUser(socket_descriptor);
        qDebug() << "disconected " << socket_descriptor;
        sockets.removeOne(socket);
        socket->deleteLater();
    });

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
            QFile file(QString::number(socket->socketDescriptor()) + "_"
                       + QDateTime::currentDateTime().toString("yyyy_MM_dd_hh-mm") + ".png");
            if (file.open(QIODevice::WriteOnly)) {
                file.write(data);
                file.close();
                qDebug() << "Screenshot saved";
            }
        }

    } else
        qDebug() << "Unable to read";
}

void Server::removeUser(qintptr socket_descriptor)
{
    for (int i = 0; i < sockets.length(); i++)
        if (sockets.at(i)->socketDescriptor() == socket_descriptor)
            sockets.remove(i);
}
