//
// Created by nullobsi on 2021/01/20.
//

#ifndef CLIGHTD_GUI_SENSORTAB_H
#define CLIGHTD_GUI_SENSORTAB_H

#include <QWidget>
#include <QLineSeries>
#include <QChart>
#include <QChartView>
#include "Sensor.h"
#include "MonitorOverride.h"
#include "SysBacklight.h"
#include "../models/RegressionPointModel.h"
#include "SensorGraph.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SensorTab; }
QT_END_NAMESPACE

class SensorTab : public QWidget {
Q_OBJECT

public:
    explicit SensorTab(QWidget *parent = nullptr);

    ~SensorTab() override;

private:
    QString serial = QString();
    QStringList serials;

    QMap<QString, MonitorOverride> overrides;

    Ui::SensorTab *ui;

    RegressionPointModel *ac;
    RegressionPointModel *bat;

    SensorGraph *acGraph;
    SensorGraph *batGraph;

    OrgClightClightConfSensorInterface *iface;
    OrgClightClightConfMonitorOverrideInterface *monIface;
    OrgClightdClightdBacklightInterface *bkIface;
};

#endif //CLIGHTD_GUI_SENSORTAB_H
