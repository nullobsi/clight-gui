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
    monIface = new OrgClightClightConfMonitorOverrideInterface("org.clight.clight", "/org/clight/clight/Conf/MonitorOverride", QDBusConnection::sessionBus(), this);


    // Create models
    ac = new RegressionPointModel(1, this, iface->acPoints());
    bat = new RegressionPointModel(0, this, iface->battPoints());

    // Create charts
    acGraph = new SensorGraph(this, tr("Screen Brightness"), ac);
    batGraph = new SensorGraph(this, tr("Screen Brightness"), bat);
    ui->acLayout->layout()->addWidget(acGraph);
    ui->batLayout->layout()->addWidget(batGraph);

    // Connect data changed
    QObject::connect(ac, &RegressionPointModel::dataUpdated, iface, &OrgClightClightConfSensorInterface::setAcPoints);
    QObject::connect(bat, &RegressionPointModel::dataUpdated, iface, &OrgClightClightConfSensorInterface::setBattPoints);

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
}
