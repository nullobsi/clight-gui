//
// Created by nullobsi on 2021/01/07.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GammaTab.h" resolved

#include "GammaTab.h"
#include "ui_GammaTab.h"

GammaTab::GammaTab(QWidget *parent) :
        QWidget(parent), ui(new Ui::GammaTab) {
    ui->setupUi(this);

    gammaInterface = new OrgClightClightConfGammaInterface("org.clight.clight", "/org/clight/clight/Conf/Gamma", QDBusConnection::sessionBus(), this);

    ui->ambientGamma->setChecked(gammaInterface->ambientGamma());
    ui->smoothTrans->setChecked(!gammaInterface->noSmooth());
    ui->longTrans->setChecked(gammaInterface->longTransition());

    QObject::connect(ui->ambientGamma, &QCheckBox::stateChanged, this, &GammaTab::AmbientGammaChanged);
    QObject::connect(ui->smoothTrans, &QCheckBox::stateChanged, this, &GammaTab::SmoothTransChanged);
    QObject::connect(ui->longTrans, &QCheckBox::stateChanged, this, &GammaTab::LongTransChanged);


    ui->smoothStep->setValue(gammaInterface->transStep());
    ui->transDuration->setValue(gammaInterface->transDuration());
    ui->dayTemp->setValue(gammaInterface->dayTemp());
    ui->nightTemp->setValue(gammaInterface->nightTemp());

    void (QSpinBox::* qSpinValueChanged)(int) = &QSpinBox::valueChanged;
    QObject::connect(ui->smoothStep, qSpinValueChanged, gammaInterface, &OrgClightClightConfGammaInterface::setTransStep);
    QObject::connect(ui->transDuration, qSpinValueChanged, gammaInterface, &OrgClightClightConfGammaInterface::setTransDuration);
    QObject::connect(ui->dayTemp, qSpinValueChanged, gammaInterface, &OrgClightClightConfGammaInterface::setDayTemp);
    QObject::connect(ui->nightTemp, qSpinValueChanged, gammaInterface, &OrgClightClightConfGammaInterface::setNightTemp);
}

GammaTab::~GammaTab() {
    delete ui;
    delete gammaInterface;
}

void GammaTab::AmbientGammaChanged(int v) {
    if (v == 2) {
        gammaInterface->setAmbientGamma(true);
    } else {
        gammaInterface->setAmbientGamma(false);
    }
}

void GammaTab::SmoothTransChanged(int v) {
    if (v == 2) {
        gammaInterface->setNoSmooth(false);
    } else {
        gammaInterface->setNoSmooth(true);
    }
}

void GammaTab::LongTransChanged(int v) {
    if (v == 2) {
        gammaInterface->setLongTransition(true);
    } else {
        gammaInterface->setLongTransition(false);
    }
}

void GammaTab::UpdateGamma(int v) {
    ui->currGamma->setValue(v);
}
