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
    backlightConf = new org::clight::clight::Conf::Backlight("org.clight.clight", "/org/clight/clight/Conf/Backlight", QDBusConnection::sessionBus(), this);

    QObject::connect(ui->autoCalib, &QCheckBox::stateChanged, this, &BacklightTab::autoCalibChanged);
    ui->autoCalib->setChecked(!backlightConf->noAutoCalib());

    QObject::connect(ui->lidClosed, &QCheckBox::stateChanged, this, &BacklightTab::lidClosedChanged);
    ui->lidClosed->setChecked(!backlightConf->inhibitOnLidClosed());

    QObject::connect(ui->smooth, &QCheckBox::stateChanged, this, &BacklightTab::smoothChanged);
    ui->smooth->setChecked(!backlightConf->noSmooth());

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