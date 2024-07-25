#include "clientmainwindow.h"
#include <QBuffer>
#include <QHostInfo>
#include <QScreen>
#include "ui_clientmainwindow.h"

ClientMainWindow::ClientMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientMainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::readyRead, this, &ClientMainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    connect(&timer, SIGNAL(timeout()), this, SLOT(on_timer()));
    timer.start(2000);
}

ClientMainWindow::~ClientMainWindow()
{
    delete ui;
}

void ClientMainWindow::sendToServer(User usr)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << QString("user") << usr;
    socket->write(data);
}

void ClientMainWindow::slotReadyRead()
{
    socket = (QTcpSocket *) sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);
    if (in.status() == QDataStream::Ok) {
        QString str;
        in >> str;

        QScreen *screen = QGuiApplication::primaryScreen();
        QPixmap pixmap = screen->grabWindow(0);

        QByteArray screenshotData;
        QBuffer buffer(&screenshotData);
        pixmap.save(&buffer, "PNG");

        data.clear();
        QDataStream out(&data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_15);
        out << QString("screenshot") << screenshotData;
        socket->write(data);
    }
}

void ClientMainWindow::on_btConnect_clicked()
{
    socket->connectToHost("127.0.0.1", 2323);
}

void ClientMainWindow::on_timer()
{
    User usr;
    usr.user = QHostInfo::localHostName();
    usr.ip = socket->localAddress().toString();
    usr.last_active_time = QDateTime::currentDateTime().toString();
    usr.machine = QHostInfo::localHostName();
    sendToServer(usr);
}
