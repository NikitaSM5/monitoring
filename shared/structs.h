
#ifndef STRUCTS_H
#define STRUCTS_H

#include "qdatetime.h"

struct User
{
    QString domain;
    QString machine;
    QString ip;
    QString user;
    QString last_active_time;

    friend QDataStream &operator<<(QDataStream &out, const User &user);
    friend QDataStream &operator>>(QDataStream &in, User &user);
};

QDataStream &operator<<(QDataStream &out, const User &user);
QDataStream &operator>>(QDataStream &in, User &user);

#endif
