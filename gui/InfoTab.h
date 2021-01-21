//
// Created by nullobsi on 2021/01/20.
//

#ifndef CLIGHTD_GUI_INFOTAB_H
#define CLIGHTD_GUI_INFOTAB_H

#include <QWidget>
#include "clight.h"
QT_BEGIN_NAMESPACE
namespace Ui { class InfoTab; }
QT_END_NAMESPACE

class InfoTab : public QWidget {
Q_OBJECT

public:
    explicit InfoTab(QWidget *parent = nullptr);

    ~InfoTab() override;

public slots:
    void PropertyChanged(QString interface, QVariantMap propertiesUpdated);
private:
    Ui::InfoTab *ui;

    OrgClightClightInterface *clight;

    static QString GetDayTime(int v);
    static QString GetNextEvent(int v);
    static QString GetLocation(Coordinate c);
};

#endif //CLIGHTD_GUI_INFOTAB_H
