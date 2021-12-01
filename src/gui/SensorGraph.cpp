//
// Created by nullobsi on 2021/08/15.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SensorGraph.h" resolved

#include <QValueAxis>
#include "SensorGraph.h"
#include "ui_SensorGraph.h"


SensorGraph::SensorGraph(QWidget *parent) :
        QWidget(parent), ui(new Ui::SensorGraph) {
    ui->setupUi(this);
}

SensorGraph::~SensorGraph() {
    delete ui;
}

using namespace QtCharts;
SensorGraph::SensorGraph(QWidget *parent, QString yAxisName, RegressionPointModel *m):
        QWidget(parent), ui(new Ui::SensorGraph) {
    model = m;
    ui->setupUi(this);
    // Connect models to list input
    ui->points->setModel(model);

    // Create line series
    series = new QLineSeries(this);

    // Update line series with data
    series->replace(model->getPoints());

    // Format graph
    auto xAxis = new QValueAxis(this);
    xAxis->setRange(0, 100);
    xAxis->setTickCount(11);
    xAxis->setLabelFormat("%.0f%%");
    xAxis->setTitleText(tr("Ambient Brightness"));

    auto yAxis = new QValueAxis(this);
    yAxis->setRange(0, 100);
    yAxis->setTickCount(11);
    yAxis->setLabelFormat("%.0f%%");
    yAxis->setTitleText(yAxisName);

    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);

    chart->addAxis(xAxis, Qt::AlignBottom);
    chart->addAxis(yAxis, Qt::AlignLeft);

    series->attachAxis(xAxis);
    series->attachAxis(yAxis);

    ui->chart->setChart(chart);
    ui->chart->setRenderHint(QPainter::Antialiasing);

    // connect data changed
    QObject::connect(model, &QAbstractItemModel::dataChanged, this, &SensorGraph::onDatChange);
    QObject::connect(model, &QAbstractItemModel::modelReset, this, &SensorGraph::onDatReset);
}

void SensorGraph::onDatChange(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles) {
    series->replace(model->getPoints());
}

void SensorGraph::onDatReset() {
    series->replace(model->getPoints());
}
