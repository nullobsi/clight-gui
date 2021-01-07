//
// Created by nullobsi on 2021/01/06.
//

#ifndef CLIGHTD_GUI_GAMMASMOOTH_H
#define CLIGHTD_GUI_GAMMASMOOTH_H
#include <QtDBus/QtDBus>

struct GammaSmooth {
    bool isSmooth;
    uint smoothStep;
    uint timeout;
};
Q_DECLARE_METATYPE(GammaSmooth)

QDBusArgument &operator<<(QDBusArgument &argument, const GammaSmooth &c);
const QDBusArgument &operator>>(const QDBusArgument &argument, GammaSmooth &c);
#endif //CLIGHTD_GUI_GAMMASMOOTH_H
