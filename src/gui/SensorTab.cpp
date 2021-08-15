//
// Created by nullobsi on 2021/01/20.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SensorTab.h" resolved

#include "SensorTab.h"
#include "ui_SensorTab.h"

SensorTab::SensorTab(QWidget *parent) :
        QWidget(parent), ui(new Ui::SensorTab) {
    ui->setupUi(this);
    iface = new OrgClightClightConfSensorInterface("org.clight.clight", "/org/clight/clight/Conf/Sensor", QDBusConnection::sessionBus(), this);

    // Create models
    ac = new RegressionPointModel(1, this, iface->acPoints());
    bat = new RegressionPointModel(0, this, iface->battPoints());

    // Connect data changed
    QObject::connect(ac, &RegressionPointModel::dataUpdated, iface, &OrgClightClightConfSensorInterface::setAcPoints);
    QObject::connect(bat, &RegressionPointModel::dataUpdated, iface, &OrgClightClightConfSensorInterface::setBattPoints);

    // Connect models to list input
    ui->acPoints->setModel(ac);
    ui->batPoints->setModel(bat);

    // Create line series
    acSeries = new QLineSeries(this);
    batSeries = new QLineSeries(this);

    // Update line series with data
    acSeries->replace(ac->getPoints());
    batSeries->replace(bat->getPoints());

    // Format graph
    acChart = formatChart(ui->acChart, acSeries);
    batChart = formatChart(ui->batChart, batSeries);
    ui->acChart->setChart(acChart);
    ui->batChart->setChart(batChart);
    ui->batChart->setRenderHint(QPainter::Antialiasing);
    ui->acChart->setRenderHint(QPainter::Antialiasing);

    // Update charts when model changes
    QObject::connect(ac, &QAbstractItemModel::dataChanged, this, &SensorTab::onChangeAc);
    QObject::connect(bat, &QAbstractItemModel::dataChanged, this, &SensorTab::onChangeBat);

    ui->batSamples->setValue(iface->battCaptures());
    ui->acSamples->setValue(iface->acCaptures());

    // Update dBus on UI
    void (QSpinBox::* qSpinValueChanged)(int) = &QSpinBox::valueChanged;
    QObject::connect(ui->acSamples, qSpinValueChanged, iface, &OrgClightClightConfSensorInterface::setAcCaptures);
    QObject::connect(ui->batSamples, qSpinValueChanged, iface, &OrgClightClightConfSensorInterface::setBattCaptures);


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

QChart *SensorTab::formatChart(QtCharts::QChartView *qChartView, QtCharts::QLineSeries *qLineSeries) {
    auto xAxis = new QValueAxis(this);
    xAxis->setRange(0, 100);
    xAxis->setTickCount(11);
    xAxis->setLabelFormat("%.0f%%");
    xAxis->setTitleText(tr("Ambient Brightness"));

    auto yAxis = new QValueAxis(this);
    yAxis->setRange(0, 100);
    yAxis->setTickCount(11);
    yAxis->setLabelFormat("%.0f%%");
    yAxis->setTitleText(tr("Screen Brightness"));

    auto chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(qLineSeries);

    chart->addAxis(xAxis, Qt::AlignBottom);
    chart->addAxis(yAxis, Qt::AlignLeft);

    qLineSeries->attachAxis(xAxis);
    qLineSeries->attachAxis(yAxis);

    return chart;
}
