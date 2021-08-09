//
// Created by nullobsi on 2021/01/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_KeyboardTab.h" resolved

#include "KeyboardTab.h"
#include "ui_KeyboardTab.h"

KeyboardTab::KeyboardTab(QWidget *parent) :
        QWidget(parent), ui(new Ui::KeyboardTab) {
    ui->setupUi(this);
    iface = new OrgClightClightConfKbdInterface("org.clight.clight", "/org/clight/clight/Conf/Kbd", QDBusConnection::sessionBus(), this);

    ui->enableKb->setChecked(iface->dim());
    QObject::connect(ui->enableKb, &QCheckBox::stateChanged, this, &KeyboardTab::EnabledChecked);

    void (QSpinBox::* qSpinBoxValueChanged)(int) = &QSpinBox::valueChanged;

    QObject::connect(ui->acTimeout, qSpinBoxValueChanged, iface, &OrgClightClightConfKbdInterface::setAcTimeout);
    QObject::connect(ui->batTimeout, qSpinBoxValueChanged, iface, &OrgClightClightConfKbdInterface::setBattTimeout);

    //chart
    ac = new RegressionPointModel(1, this, iface->acPoints());
    bat = new RegressionPointModel(0, this, iface->battPoints());

    QObject::connect(ac, &RegressionPointModel::dataUpdated, iface, &OrgClightClightConfKbdInterface::setAcPoints);
    QObject::connect(bat, &RegressionPointModel::dataUpdated, iface, &OrgClightClightConfKbdInterface::setAcPoints);

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
    xAxis->setTitleText(tr("Ambient Brightness"));

    auto yAxis = new QValueAxis();
    yAxis->setRange(0, 100);
    yAxis->setTickCount(11);
    yAxis->setLabelFormat("%.0f%%");
    yAxis->setTitleText(tr("Keyboard Brightness"));

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
    xAxis1->setTitleText(tr("Ambient Brightness"));

    auto yAxis1 = new QValueAxis();
    yAxis1->setRange(0, 100);
    yAxis1->setTickCount(11);
    yAxis1->setLabelFormat("%.0f%%");
    yAxis1->setTitleText(tr("Keyboard Brightness"));

    batChart = new QChart();
    batChart->legend()->hide();

    batChart->addSeries(batSeries);

    batChart->addAxis(xAxis1, Qt::AlignBottom);
    batChart->addAxis(yAxis1, Qt::AlignLeft);

    batSeries->attachAxis(xAxis1);
    batSeries->attachAxis(yAxis1);

    ui->acChart->setChart(acChart);
    ui->batChart->setChart(batChart);

    QObject::connect(ac, &QAbstractItemModel::dataChanged, this, &KeyboardTab::onChangeAc);
    QObject::connect(bat, &QAbstractItemModel::dataChanged, this, &KeyboardTab::onChangeBat);

    ui->batChart->setRenderHint(QPainter::Antialiasing);
    ui->acChart->setRenderHint(QPainter::Antialiasing);
}

KeyboardTab::~KeyboardTab() {
    delete ui;
}

void KeyboardTab::EnabledChecked(int state) {
    if (state == 2){
        iface->setDim(true);
    } else {
        iface->setDim(false);
    }
}

void KeyboardTab::onChangeBat(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles) {
    qDebug() << "bat changed";
    batSeries->replace(bat->getPoints());
}

void KeyboardTab::onChangeAc(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles) {
    qDebug() << "ac changed";
    acSeries->replace(ac->getPoints());
}