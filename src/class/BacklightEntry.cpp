//
// Created by nullobsi on 2021/01/06.
//

#include "BacklightEntry.h"

QDBusArgument &operator<<(QDBusArgument &argument, const BacklightEntry &c) {
    argument.beginStructure();
    argument << c.serial << c.percent;
    argument.endStructure();
    return argument;
}
const QDBusArgument &operator>>(const QDBusArgument &argument, BacklightEntry &c) {
    argument.beginStructure();
    argument >> c.serial >> c.percent;
    argument.endStructure();
    return argument;
}