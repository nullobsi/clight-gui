//
// Created by nullobsi on 2021/01/07.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DimmerTab.h" resolved

#include "DimmerTab.h"
#include "ui_DimmerTab.h"

DimmerTab::DimmerTab(QWidget *parent) :
        QWidget(parent), ui(new Ui::DimmerTab) {
    ui->setupUi(this);
    iface = new OrgClightClightConfDimmerInterface("org.clight.clight", "/org/clight/clight/Conf/Dimmer", QDBusConnection::sessionBus(), this);

    void (QSpinBox::* qSpinValueChanged)(int) = &QSpinBox::valueChanged;
    void (QDoubleSpinBox::* qDoubleSpinValueChanged)(double) = &QDoubleSpinBox::valueChanged;

    QObject::connect(ui->dimStep, qDoubleSpinValueChanged, iface, &OrgClightClightConfDimmerInterface::setTransStepEnter);
    ui->dimStep->setValue(iface->transStepEnter());

    QObject::connect(ui->undimStep, qDoubleSpinValueChanged, iface, &OrgClightClightConfDimmerInterface::setTransStepExit);
    ui->undimStep->setValue(iface->transStepExit());

    QObject::connect(ui->dimTime, qSpinValueChanged, iface, &OrgClightClightConfDimmerInterface::setTransDurationEnter);
    ui->dimTime->setValue(iface->transDurationEnter());

    QObject::connect(ui->undimTime, qSpinValueChanged, iface, &OrgClightClightConfDimmerInterface::setTransDurationExit);
    ui->undimTime->setValue(iface->transDurationExit());

    QObject::connect(ui->acTimeout, qSpinValueChanged, iface, &OrgClightClightConfDimmerInterface::setAcTimeout);
    ui->acTimeout->setValue(iface->acTimeout());

    QObject::connect(ui->battTimeout, qSpinValueChanged, iface, &OrgClightClightConfDimmerInterface::setBattTimeout);
    ui->battTimeout->setValue(iface->battTimeout());

    QObject::connect(ui->smoothDim, &QCheckBox::stateChanged, this, &DimmerTab::smoothDimChanged);
    ui->smoothDim->setChecked(!iface->noSmoothEnter());

    QObject::connect(ui->smoothUndim, &QCheckBox::stateChanged, this, &DimmerTab::smoothUndimChanged);
    ui->smoothUndim->setChecked(!iface->noSmoothExit());

    QObject::connect(ui->dimPct, qDoubleSpinValueChanged, iface, &OrgClightClightConfDimmerInterface::setDimmedPct);
    ui->dimPct->setValue(iface->dimmedPct());
}

DimmerTab::~DimmerTab() {
    delete ui;
}

void DimmerTab::smoothDimChanged(int v) {
    if (v == 2) {
        iface->setNoSmoothEnter(false);
    } else {
        iface->setNoSmoothEnter(true);
    }
}

void DimmerTab::smoothUndimChanged(int v) {
    if (v == 2) {
        iface->setNoSmoothExit(false);
    } else {
        iface->setNoSmoothExit(true);
    }
}
