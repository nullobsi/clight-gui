//
// Created by nullobsi on 2021/01/06.
//

#ifndef CLIGHTD_GUI_COORDINATE_H
#define CLIGHTD_GUI_COORDINATE_H

#include <QtDBus/QtDBus>
struct Coordinate {
    double lat;
    double lon;
};
Q_DECLARE_METATYPE(Coordinate)

QDBusArgument &operator<<(QDBusArgument &argument, const Coordinate &c);
const QDBusArgument &operator>>(const QDBusArgument &argument, Coordinate &c);

#endif //CLIGHTD_GUI_COORDINATE_H
