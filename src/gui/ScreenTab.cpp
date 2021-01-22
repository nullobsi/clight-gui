//
// Created by nullobsi on 2021/01/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ScreenTab.h" resolved

#include "ScreenTab.h"
#include "ui_ScreenTab.h"

ScreenTab::ScreenTab(QWidget *parent) :
        QWidget(parent), ui(new Ui::ScreenTab) {
    ui->setupUi(this);
    iface = new OrgClightClightConfScreenInterface("org.clight.clight", "/org/clight/clight/Conf/Screen", QDBusConnection::sessionBus(), this);

    ui->acTimeout->setValue(iface->acTimeout());
    ui->batTimeout->setValue(iface->battTimeout());
    ui->numSamples->setValue(iface->numSamples());
    void (QSpinBox::* qspinChanged)(int) = &QSpinBox::valueChanged;
    QObject::connect(ui->batTimeout, qspinChanged, iface, &OrgClightClightConfScreenInterface::setBattTimeout);
    QObject::connect(ui->acTimeout, qspinChanged, iface, &OrgClightClightConfScreenInterface::setAcTimeout);
}

ScreenTab::~ScreenTab() {
    delete ui;
    delete iface;
}
