//
// Created by nullobsi on 2021/01/25.
//

#include "ScrollSysTray.h"

ScrollSysTray::ScrollSysTray(QObject *parent) : QSystemTrayIcon(parent) {

}

bool ScrollSysTray::event(QEvent *e) {
    if (e->type() == QEvent::Wheel) {
        auto *wheelEvent = dynamic_cast<QWheelEvent*>(e);
        combinedDelta += wheelEvent->angleDelta().y();
        wheelEvent->accept();

        if (combinedDelta > 120) {
            emit ScrollUp();
            combinedDelta = 0;
        } else if (combinedDelta < -120) {
            emit ScrollDown();
            combinedDelta = 0;
        }
        return true;
    } else {
        return QSystemTrayIcon::event(e);
    }
}

ScrollSysTray::ScrollSysTray(const QIcon &icon, QObject *parent) : QSystemTrayIcon(icon, parent) {

}
