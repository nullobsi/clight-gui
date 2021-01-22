//
// Created by nullobsi on 2021/01/06.
//

#ifndef CLIGHTD_GUI_BACKLIGHTENTRY_H
#define CLIGHTD_GUI_BACKLIGHTENTRY_H
#include <QString>
#include <QList>
#include <QtDBus/QtDBus>

struct BacklightEntry {
    QString serial;
    double percent;
};

typedef QList<BacklightEntry> BacklightList;

Q_DECLARE_METATYPE(BacklightEntry);
Q_DECLARE_METATYPE(BacklightList);

QDBusArgument &operator<<(QDBusArgument &argument, const BacklightEntry &c);
const QDBusArgument &operator>>(const QDBusArgument &argument, BacklightEntry &c);

#endif //CLIGHTD_GUI_BACKLIGHTENTRY_H
