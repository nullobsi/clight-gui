//
// Created by nullobsi on 2021/01/07.
//

#ifndef CLIGHTD_GUI_DIMMERTAB_H
#define CLIGHTD_GUI_DIMMERTAB_H

#include <QWidget>
#include "Dimmer.h"
#include "Dpms.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DimmerTab; }
QT_END_NAMESPACE

class DimmerTab : public QWidget {
Q_OBJECT

public:
    explicit DimmerTab(QWidget *parent = nullptr);

    ~DimmerTab() override;

public slots:
    void smoothDimChanged(int v);
    void smoothUndimChanged(int v);

private:
    Ui::DimmerTab *ui;
    OrgClightClightConfDimmerInterface *iface;
    OrgClightClightConfDpmsInterface *dpms;
};

#endif //CLIGHTD_GUI_DIMMERTAB_H
