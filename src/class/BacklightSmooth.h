//
// Created by nullobsi on 2021/01/06.
//

#ifndef CLIGHTD_GUI_BACKLIGHTSMOOTH_H
#define CLIGHTD_GUI_BACKLIGHTSMOOTH_H
#include <QtDBus/QtDBus>

struct BacklightSmooth {
    bool isSmooth;
    double smoothStep;
    uint timeout;
};
Q_DECLARE_METATYPE(BacklightSmooth)

QDBusArgument &operator<<(QDBusArgument &argument, const BacklightSmooth &c);
const QDBusArgument &operator>>(const QDBusArgument &argument, BacklightSmooth &c);

#endif //CLIGHTD_GUI_BACKLIGHTSMOOTH_H
