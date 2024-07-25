#include "structs.h"

QDataStream &operator<<(QDataStream &out, const User &user)
{
    out << user.domain << user.machine << user.ip << user.user << user.last_active_time;
    return out;
}

QDataStream &operator>>(QDataStream &in, User &user)
{
    in >> user.domain >> user.machine >> user.ip >> user.user >> user.last_active_time;
    return in;
}
