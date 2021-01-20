//
// Created by nullobsi on 2021/01/20.
//

#ifndef CLIGHTD_GUI_PROPERTIESSTRUCT_H
#define CLIGHTD_GUI_PROPERTIESSTRUCT_H
#include <QString>
#include <QDBusVariant>
#include <QtDBus/qdbusmetatype.h>

struct PropertiesStruct {
    QString property;
    QDBusVariant value;
};
QDBusArgument &operator<<(QDBusArgument &argument, const PropertiesStruct &c);
const QDBusArgument &operator>>(const QDBusArgument &argument, PropertiesStruct &c);

typedef QList<PropertiesStruct> PropertiesList;

Q_DECLARE_METATYPE(PropertiesStruct)
Q_DECLARE_METATYPE(PropertiesList)

#endif //CLIGHTD_GUI_PROPERTIESSTRUCT_H
