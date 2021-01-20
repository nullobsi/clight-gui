//
// Created by nullobsi on 2021/01/07.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BacklightTab.h" resolved

#include "BacklightTab.h"
#include "ui_BacklightTab.h"

BacklightTab::BacklightTab(QWidget *parent) :
        QWidget(parent), ui(new Ui::BacklightTab) {
    ui->setupUi(this);
    backlightStat = new BacklightPctModel(this);
    backlightConf = new OrgClightClightConfBacklightInterface("org.clight.clight", "/org/clight/clight/Conf/Backlight", QDBusConnection::sessionBus(), this);

    QObject::connect(ui->autoCalib, &QCheckBox::stateChanged, this, &BacklightTab::autoCalibChanged);
    ui->autoCalib->setChecked(!backlightConf->noAutoCalib());

    QObject::connect(ui->lidClosed, &QCheckBox::stateChanged, this, &BacklightTab::lidClosedChanged);
    ui->lidClosed->setChecked(!backlightConf->inhibitOnLidClosed());

    QObject::connect(ui->smooth, &QCheckBox::stateChanged, this, &BacklightTab::smoothChanged);
    ui->smooth->setChecked(!backlightConf->noSmooth());

    void (QSpinBox::* qSpinValueChanged)(int) = &QSpinBox::valueChanged;
    void (QDoubleSpinBox::* qDoubleSpinValueChanged)(double) = &QDoubleSpinBox::valueChanged;

    QObject::connect(ui->acDay, qSpinValueChanged, this->backlightConf, &OrgClightClightConfBacklightInterface::setAcDayTimeout);
    ui->acDay->setValue(backlightConf->acDayTimeout());

    QObject::connect(ui->acNight, qSpinValueChanged, this->backlightConf, &OrgClightClightConfBacklightInterface::setAcNightTimeout);
    ui->acNight->setValue(backlightConf->acNightTimeout());

    QObject::connect(ui->acEvent, qSpinValueChanged, this->backlightConf, &OrgClightClightConfBacklightInterface::setAcEventTimeout);
    ui->acEvent->setValue(backlightConf->acEventTimeout());

    QObject::connect(ui->batteryDay, qSpinValueChanged, this->backlightConf, &OrgClightClightConfBacklightInterface::setBattDayTimeout);
    ui->batteryDay->setValue(backlightConf->battDayTimeout());

    QObject::connect(ui->batteryNight, qSpinValueChanged, this->backlightConf, &OrgClightClightConfBacklightInterface::setBattNightTimeout);
    ui->batteryNight->setValue(backlightConf->battNightTimeout());

    QObject::connect(ui->batteryEvent, qSpinValueChanged, this->backlightConf, &OrgClightClightConfBacklightInterface::setBattEventTimeout);
    ui->batteryEvent->setValue(backlightConf->battEventTimeout());

    QObject::connect(ui->smoothLength, qSpinValueChanged, this->backlightConf, &OrgClightClightConfBacklightInterface::setTransDuration);
    ui->smoothLength->setValue(backlightConf->transDuration());

    QObject::connect(ui->smoothStep, qDoubleSpinValueChanged, this->backlightConf, &OrgClightClightConfBacklightInterface::setTransStep);
    ui->smoothStep->setValue(backlightConf->transStep());


    ui->brightnessTable->setModel(backlightStat);
}

BacklightTab::~BacklightTab() {
    delete ui;
    delete backlightStat;
    delete backlightConf;
}

void BacklightTab::autoCalibChanged(int v) {
    if (v == 2) {
        backlightConf->setNoAutoCalib(false);
    } else {
        backlightConf->setNoAutoCalib(true);
    }
}

void BacklightTab::lidClosedChanged(int v) {
    if (v == 2) {
        backlightConf->setInhibitOnLidClosed(false);
    } else {
        backlightConf->setInhibitOnLidClosed(true);
    }
}

void BacklightTab::smoothChanged(int v) {
    if (v == 2) {
        backlightConf->setNoSmooth(false);
    } else {
        backlightConf->setNoSmooth(true);
    }
}