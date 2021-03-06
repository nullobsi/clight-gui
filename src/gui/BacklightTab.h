//
// Created by nullobsi on 2021/01/07.
//

#ifndef CLIGHTD_GUI_BACKLIGHTTAB_H
#define CLIGHTD_GUI_BACKLIGHTTAB_H

#include <QWidget>
#include "../models/BacklightPctModel.h"
#include "Backlight.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BacklightTab; }
QT_END_NAMESPACE

class BacklightTab : public QWidget {
Q_OBJECT

public:
    explicit BacklightTab(QWidget *parent = nullptr);

    ~BacklightTab() override;

    bool AutoCalib();
public slots:
    void autoCalibChanged(int v);
    void lidClosedChanged(int v);
    void smoothChanged(int v);
signals:
    void AutoCalibChanged(bool n);
private:
    Ui::BacklightTab *ui;
    BacklightPctModel *backlightStat;
    OrgClightClightConfBacklightInterface *backlightConf;
};

#endif //CLIGHTD_GUI_BACKLIGHTTAB_H
