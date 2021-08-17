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
#include "AddOverrideDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SensorTab; }
QT_END_NAMESPACE

class SensorTab : public QWidget {
Q_OBJECT

public:
    explicit SensorTab(QWidget *parent = nullptr);

    ~SensorTab() override;

public slots:
    void addBtnClicked();
    void rmBtnClicked();
    void serialChanged(int index);

    void acPointsUpdated(QList<double> points);
    void batPointsUpdated(QList<double> points);

    void dialogFinished(int code);

private:
    QString serial = QString();
    int boxIndex = 0;

    QStringList serials;

    QMap<QString, MonitorOverride> overrides;

    Ui::SensorTab *ui;

    AddOverrideDialog *dialog = nullptr;

    RegressionPointModel *ac;
    RegressionPointModel *bat;

    SensorGraph *acGraph;
    SensorGraph *batGraph;

    OrgClightClightConfSensorInterface *iface;
    OrgClightClightConfMonitorOverrideInterface *monIface;
    OrgClightdClightdBacklightInterface *bkIface;
};

#endif //CLIGHTD_GUI_SENSORTAB_H
