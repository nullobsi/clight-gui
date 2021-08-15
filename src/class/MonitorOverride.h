//
// Created by nullobsi on 2021/08/15.
//

#ifndef CLIGHT_GUI_MONITOROVERRIDE_H
#define CLIGHT_GUI_MONITOROVERRIDE_H

#include "SensorFrames.h"

struct MonitorOverride {
    QString serial;
    SensorFrames ac;
    SensorFrames bat;
};

typedef QList<MonitorOverride> MonitorOverrideList;

Q_DECLARE_METATYPE(MonitorOverride);
Q_DECLARE_METATYPE(MonitorOverrideList);

QDBusArgument &operator<<(QDBusArgument &argument, const MonitorOverride &c);
const QDBusArgument &operator>>(const QDBusArgument &argument, MonitorOverride &c);

#endif //CLIGHT_GUI_MONITOROVERRIDE_H
