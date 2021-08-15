//
// Created by nullobsi on 2021/08/15.
//

#include "MonitorOverride.h"

QDBusArgument &operator<<(QDBusArgument &argument, const MonitorOverride &c) {
    argument.beginStructure();
    argument << c.serial << c.ac << c.bat;
    argument.endStructure();
    return argument;
}
const QDBusArgument &operator>>(const QDBusArgument &argument, MonitorOverride &c) {
    argument.beginStructure();
    argument >> c.serial >> c.ac >> c.bat;
    argument.endStructure();
    return argument;
}