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
    inhib = new OrgClightClightConfInhibitInterface("org.clight.clight", "/org/clight/clight/Conf/Inhibit", QDBusConnection::sessionBus(), this);
    //properties = new OrgFreedesktopDBusPropertiesInterface("org.clight.clight", "/org/clight/clight", QDBusConnection::sessionBus(), this);

    ui->sunriseDate->setDateTime(QDateTime::fromSecsSinceEpoch(clight->sunrise()));
    ui->sunsetDate->setDateTime(QDateTime::fromSecsSinceEpoch(clight->sunset()));
    ui->currentEvent->setText(GetDayTime(clight->dayTime()));
    ui->nextEvent->setText(GetNextEvent(clight->nextEvent()));
    ui->inEvent->setChecked(clight->inEvent());
    ui->location->setText(GetLocation(clight->location()));

    ui->isSuspended->setChecked(clight->suspended());
    ui->isInhibited->setChecked(clight->inhibited());
    ui->pmInhibited->setChecked(clight->pmInhibited());

    ui->sensorAvailable->setChecked(clight->sensorAvail());
    ui->ambientBrightness->setValue((int)(clight->ambientBr()*100));
    ui->screenComp->setValue(clight->screenComp());

    QDBusConnection::sessionBus().connect("org.clight.clight", "/org/clight/clight", "org.freedesktop.DBus.Properties", "PropertiesChanged", this, SLOT(PropertyChanged(QString, QVariantMap)));

    ui->autoInhibitPm->setChecked(inhib->inhibitPM());
    ui->dockInhibit->setChecked(inhib->inhibitDocked());
    QObject::connect(ui->autoInhibitPm, &QCheckBox::stateChanged, this, &InfoTab::AutoInhibChanged);
    QObject::connect(ui->dockInhibit, &QCheckBox::stateChanged, this, &InfoTab::DockInhibChanged);
    //QObject::connect(this->properties, &OrgFreedesktopDBusPropertiesInterface::PropertiesChanged, this, &InfoTab::PropertyChanged);
}

InfoTab::~InfoTab() {
    delete ui;
    delete clight;
}

void InfoTab::PropertyChanged(QString interface, QVariantMap propertiesUpdated) {
    if (interface == "org.clight.clight") {
        auto keys = propertiesUpdated.keys();
        for (const QString& p : keys) {
            const QVariant v = propertiesUpdated.value(p);

            if (p == "Sunrise") {
                ui->sunriseDate->setDateTime(QDateTime::fromSecsSinceEpoch(v.toLongLong()));
            } else if (p == "Sunset") {
                ui->sunsetDate->setDateTime(QDateTime::fromSecsSinceEpoch(v.toLongLong()));
            } else if (p == "DayTime") {
                ui->currentEvent->setText(GetDayTime(v.toInt()));
            } else if (p == "NextEvent") {
                ui->nextEvent->setText(GetNextEvent(v.toInt()));
            } else if (p == "InEvent") {
                ui->inEvent->setChecked(v.toBool());
            } else if (p == "Location") {
                ui->location->setText(GetLocation(v.value<Coordinate>()));
            } else if (p == "Suspended") {
                ui->isSuspended->setChecked(v.toBool());
            } else if (p == "Inhibited") {
                ui->isInhibited->setChecked(v.toBool());
            } else if (p == "PmInhibited") {
                ui->pmInhibited->setChecked(v.toBool());
            } else if (p == "SensorAvail") {
                ui->sensorAvailable->setChecked(v.toBool());
            } else if (p == "AmbientBr") {
                ui->ambientBrightness->setValue((int)(v.toDouble()*100));
            } else if (p == "ScreenComp") {
                ui->screenComp->setValue(v.toDouble());
            }
        }
    }
}

QString InfoTab::GetDayTime(int v) {
    if (v) {
        return "Night";
    }
    return "Day";
}

QString InfoTab::GetNextEvent(int v) {
    if (v) {
        return "Sunset";
    }
    return "Sunrise";
}

QString InfoTab::GetLocation(Coordinate c) {
    return QString::number(c.lat, 'f', 3) + ", " + QString::number(c.lon, 'f', 3);
}

void InfoTab::AutoInhibChanged(int v) {
    if (v == 2) {
        inhib->setInhibitPM(true);
    } else {
        inhib->setInhibitPM(false);
    }
}

void InfoTab::DockInhibChanged(int v) {
    if (v == 2) {
        inhib->setInhibitDocked(true);
    } else {
        inhib->setInhibitDocked(false);
    }
}
