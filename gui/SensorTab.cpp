//
// Created by nullobsi on 2021/01/20.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SensorTab.h" resolved

#include "SensorTab.h"
#include "ui_SensorTab.h"

SensorTab::SensorTab(QWidget *parent) :
        QWidget(parent), ui(new Ui::SensorTab) {
    ui->setupUi(this);

    ac = new RegressionPointModel(1, this);
    bat = new RegressionPointModel(0, this);

    ui->acPoints->setModel(ac);
    ui->batPoints->setModel(bat);

    acSeries = new QLineSeries(this);
    batSeries = new QLineSeries(this);

    acSeries->replace(ac->getPoints());
    batSeries->replace(bat->getPoints());

    auto xAxis = new QValueAxis();
    xAxis->setRange(0, 100);
    xAxis->setTickCount(11);
    xAxis->setLabelFormat("%.0f%%");
    xAxis->setTitleText("Ambient Brightness");

    auto yAxis = new QValueAxis();
    yAxis->setRange(0, 100);
    yAxis->setTickCount(11);
    yAxis->setLabelFormat("%.0f%%");
    yAxis->setTitleText("Screen Brightness");

    acChart = new QChart();
    acChart->legend()->hide();
    acChart->addSeries(acSeries);

    acChart->addAxis(xAxis, Qt::AlignBottom);
    acChart->addAxis(yAxis, Qt::AlignLeft);

    acSeries->attachAxis(xAxis);
    acSeries->attachAxis(yAxis);
    auto xAxis1 = new QValueAxis();
    xAxis1->setRange(0, 100);
    xAxis1->setTickCount(11);
    xAxis1->setLabelFormat("%.0f%%");
    xAxis1->setTitleText("Ambient Brightness");

    auto yAxis1 = new QValueAxis();
    yAxis1->setRange(0, 100);
    yAxis1->setTickCount(11);
    yAxis1->setLabelFormat("%.0f%%");
    yAxis1->setTitleText("Screen Brightness");

    batChart = new QChart();
    batChart->legend()->hide();

    batChart->addSeries(batSeries);

    batChart->addAxis(xAxis1, Qt::AlignBottom);
    batChart->addAxis(yAxis1, Qt::AlignLeft);

    batSeries->attachAxis(xAxis1);
    batSeries->attachAxis(yAxis1);

    ui->acChart->setChart(acChart);
    ui->batChart->setChart(batChart);

    QObject::connect(ac, &QAbstractItemModel::dataChanged, this, &SensorTab::onChangeAc);
    QObject::connect(bat, &QAbstractItemModel::dataChanged, this, &SensorTab::onChangeBat);
}

SensorTab::~SensorTab() {
    delete ui;

    delete ac;
    delete bat;

    delete acSeries;
    delete batSeries;

    delete acChart;
    delete batChart;
}

void SensorTab::onChangeBat(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles) {
    qDebug() << "bat changed";
    batSeries->replace(bat->getPoints());
}

void SensorTab::onChangeAc(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles) {
    qDebug() << "ac changed";
    acSeries->replace(ac->getPoints());
}
