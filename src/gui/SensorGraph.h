//
// Created by nullobsi on 2021/08/15.
//

#ifndef CLIGHT_GUI_SENSORGRAPH_H
#define CLIGHT_GUI_SENSORGRAPH_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QAbstractItemModel>
#include "../models/RegressionPointModel.h"


QT_BEGIN_NAMESPACE
namespace Ui { class SensorGraph; }
QT_END_NAMESPACE

class SensorGraph : public QWidget {
Q_OBJECT

public:
    explicit SensorGraph(QWidget *parent = nullptr);
    SensorGraph(QWidget *parent, QString yAxisName, RegressionPointModel *m);

    ~SensorGraph() override;

public slots:
    void onDatChange(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());

private:
    QtCharts::QLineSeries *series;
    QtCharts::QChart *chart;
    RegressionPointModel *model;

    Ui::SensorGraph *ui;
};


#endif //CLIGHT_GUI_SENSORGRAPH_H
