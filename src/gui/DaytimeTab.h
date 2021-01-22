//
// Created by nullobsi on 2021/01/21.
//

#ifndef CLIGHTD_GUI_DAYTIMETAB_H
#define CLIGHTD_GUI_DAYTIMETAB_H

#include <QWidget>
#include "Daytime.h"
QT_BEGIN_NAMESPACE
namespace Ui { class DaytimeTab; }
QT_END_NAMESPACE

class DaytimeTab : public QWidget {
Q_OBJECT

public:
    explicit DaytimeTab(QWidget *parent = nullptr);

    ~DaytimeTab() override;
public slots:
    void sunsetChanged(const QTime &time);
    void sunriseChanged(const QTime &time);

    void sunsetDel();
    void sunriseDel();
private:
    Ui::DaytimeTab *ui;
    OrgClightClightConfDaytimeInterface *iface;
};

#endif //CLIGHTD_GUI_DAYTIMETAB_H
