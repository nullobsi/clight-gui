//
// Created by nullobsi on 2021/01/06.
//

#include "Coordinate.h"
#include <QtDBus/QtDBus>

QDBusArgument &operator<<(QDBusArgument &argument, const Coordinate &c) {
    argument.beginStructure();
    argument << c.lat << c.lon;
    argument.endStructure();
    return argument;
}
const QDBusArgument &operator>>(const QDBusArgument &argument, Coordinate &c) {
    argument.beginStructure();
    argument >> c.lat >> c.lon;
    argument.endStructure();
    return argument;
}

