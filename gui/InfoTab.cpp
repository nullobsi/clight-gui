//
// Created by nullobsi on 2021/01/20.
//

// You may need to build the project (run Qt uic code generator) to get "ui_InfoTab.h" resolved

#include "InfoTab.h"
#include "ui_InfoTab.h"

InfoTab::InfoTab(QWidget *parent) :
        QWidget(parent), ui(new Ui::InfoTab) {
    ui->setupUi(this);
    clight = new OrgClightClightInterface("org.clight.clight", "/org/clight/clight", QDBusConnection::sessionBus(), this);
    properties = new OrgFreedesktopDBusPropertiesInterface("org.clight.clight", "/org/clight/clight", QDBusConnection::sessionBus(), this);

    ui->sunriseDate->setDateTime(QDateTime::fromSecsSinceEpoch(clight->sunrise()));
    ui->sunsetDate->setDateTime(QDateTime::fromSecsSinceEpoch(clight->sunset()));

    QObject::connect(properties, &OrgFreedesktopDBusPropertiesInterface::PropertiesChanged, this, &InfoTab::PropertyChanged);
}

InfoTab::~InfoTab() {
    delete ui;
    delete clight;
}

void InfoTab::PropertyChanged(QString interface, PropertiesList propertiesUpdated, QStringList invalidProperties) {
    if (interface == "org.clight.clight") {
        int num = propertiesUpdated.size();
        for (int i = 0; i < num; i ++) {
            const PropertiesStruct& s = propertiesUpdated.at(i);
            if (s.property == "Sunrise") {
                ui->sunriseDate->setDateTime(QDateTime::fromSecsSinceEpoch(s.value.variant().toLongLong()));
            } else if (s.property == "Sunset") {
                ui->sunsetDate->setDateTime(QDateTime::fromSecsSinceEpoch(s.value.variant().toLongLong()));
            }
        }
    }
}
