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
#include "../models/RegressionPointModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SensorTab; }
QT_END_NAMESPACE

class SensorTab : public QWidget {
Q_OBJECT

public:
    explicit SensorTab(QWidget *parent = nullptr);

    ~SensorTab() override;

public slots:
    void onChangeBat(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());
    void onChangeAc(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());

private:
    QtCharts::QChart *formatChart(QtCharts::QChartView *, QtCharts::QLineSeries *);
    Ui::SensorTab *ui;

    RegressionPointModel *ac;
    RegressionPointModel *bat;

    QtCharts::QLineSeries *acSeries;
    QtCharts::QLineSeries *batSeries;

    QtCharts::QChart *acChart;
    QtCharts::QChart *batChart;

    OrgClightClightConfSensorInterface *iface;
};

#endif //CLIGHTD_GUI_SENSORTAB_H
