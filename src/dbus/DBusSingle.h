//
// Created by nullobsi on 2021/01/22.
//

#ifndef CLIGHT_GUI_DBUSSINGLE_H
#define CLIGHT_GUI_DBUSSINGLE_H

#include <QDBusAbstractAdaptor>
class DBusSingle : public QDBusAbstractAdaptor {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.clightgui.App")

public:
    explicit DBusSingle(QObject *parent = nullptr);

signals:
    void WindowOpenRequest();

public slots:
    Q_NOREPLY [[maybe_unused]] void ShowWindow();
};


#endif //CLIGHT_GUI_DBUSSINGLE_H
