//
// Created by nullobsi on 2021/01/06.
//

#include "BacklightSmooth.h"

QDBusArgument &operator<<(QDBusArgument &argument, const BacklightSmooth &c) {
    argument.beginStructure();
    argument << c.isSmooth << c.smoothStep << c.timeout;
    argument.endStructure();
    return argument;
}
const QDBusArgument &operator>>(const QDBusArgument &argument, BacklightSmooth &c) {
    argument.beginStructure();
    argument >> c.isSmooth >> c.smoothStep >> c.timeout;
    argument.endStructure();
    return argument;
}
