//
// Created by nullobsi on 2021/01/20.
//

#include "PropertiesStruct.h"

QDBusArgument &operator<<(QDBusArgument &argument, const PropertiesStruct &c) {
    argument.beginStructure();
    argument << c.property << c.value;
    argument.endStructure();
    return argument;
}
const QDBusArgument &operator>>(const QDBusArgument &argument, PropertiesStruct &c) {
    argument.beginStructure();
    argument >> c.property >> c.value;
    argument.endStructure();
    return argument;
}