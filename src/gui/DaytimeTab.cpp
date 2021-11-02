//
// Created by nullobsi on 2021/01/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DaytimeTab.h" resolved

#include "DaytimeTab.h"
#include "ui_DaytimeTab.h"

DaytimeTab::DaytimeTab(QWidget *parent) :
        QWidget(parent), ui(new Ui::DaytimeTab) {
    ui->setupUi(this);
    iface = new OrgClightClightConfDaytimeInterface("org.clight.clight", "/org/clight/clight/Conf/Daytime", QDBusConnection::sessionBus(), this);
    ui->sunset->setDateTime(QDateTime::fromString(iface->sunset(), "H:mm"));
    ui->sunrise->setDateTime(QDateTime::fromString(iface->sunrise(), "H:mm"));
    auto loc = iface->location();
    ui->lat->setValue(loc.lat);
    ui->lon->setValue(loc.lon);
    ui->eventDuration->setValue(iface->eventDuration());

    QObject::connect(ui->sunset, &QTimeEdit::userTimeChanged, this, &DaytimeTab::sunsetChanged);
    QObject::connect(ui->sunrise, &QTimeEdit::userTimeChanged, this, &DaytimeTab::sunriseChanged);

    QObject::connect(ui->delSunset, &QPushButton::clicked, this, &DaytimeTab::sunsetDel);
    QObject::connect(ui->delSunrise, &QPushButton::clicked, this, &DaytimeTab::sunriseDel);

    void (QDoubleSpinBox::* qDoubleSpinValueChanged)(double) = &QDoubleSpinBox::valueChanged;
    QObject::connect(ui->lat, qDoubleSpinValueChanged, this, &DaytimeTab::locationChanged);
    QObject::connect(ui->lon, qDoubleSpinValueChanged, this, &DaytimeTab::locationChanged);
}

DaytimeTab::~DaytimeTab() {
    delete ui;
    delete iface;
}

void DaytimeTab::sunsetChanged(const QTime &time) {
    iface->setSunset(time.toString("H:mm"));
}

void DaytimeTab::sunriseChanged(const QTime &time) {
    iface->setSunrise(time.toString("H:mm"));
}

void DaytimeTab::sunsetDel() {
    iface->setSunset("");
}

void DaytimeTab::sunriseDel() {
    iface->setSunrise("");
}

void DaytimeTab::locationChanged(double v) {
    iface->setLocation(Coordinate {
        .lat = ui->lat->value(),
        .lon = ui->lon->value()
    });
}
