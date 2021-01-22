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
    ui->offThresh->setValue(iface->ambBrThresh());
    QObject::connect(ui->enableKb, &QCheckBox::stateChanged, this, &KeyboardTab::EnabledChecked);

    void (QDoubleSpinBox::* qDoubleSpinValueChanged)(double) = &QDoubleSpinBox::valueChanged;
    QObject::connect(ui->offThresh, qDoubleSpinValueChanged, iface, &OrgClightClightConfKbdInterface::setAmbBrThresh);
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
