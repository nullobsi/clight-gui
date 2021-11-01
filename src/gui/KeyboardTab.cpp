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

    // Create charts
    acGraph = new SensorGraph(this, tr("Keyboard Brightness"), ac);
    batGraph = new SensorGraph(this, tr("Keyboard Brightness"), bat);
    ui->acLayout->layout()->addWidget(acGraph);
    ui->batLayout->layout()->addWidget(batGraph);

    QObject::connect(ac, &RegressionPointModel::dataUpdated, iface, &OrgClightClightConfKbdInterface::setAcPoints);
    QObject::connect(bat, &RegressionPointModel::dataUpdated, iface, &OrgClightClightConfKbdInterface::setBattPoints);
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