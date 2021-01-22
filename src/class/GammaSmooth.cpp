//
// Created by nullobsi on 2021/01/06.
//

#include "GammaSmooth.h"

QDBusArgument &operator<<(QDBusArgument &argument, const GammaSmooth &c) {
    argument.beginStructure();
    argument << c.isSmooth << c.smoothStep << c.timeout;
    argument.endStructure();
    return argument;
}
const QDBusArgument &operator>>(const QDBusArgument &argument, GammaSmooth &c) {
    argument.beginStructure();
    argument >> c.isSmooth >> c.smoothStep >> c.timeout;
    argument.endStructure();
    return argument;
}