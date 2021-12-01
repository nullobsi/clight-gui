//
// Created by nullobsi on 2021/01/20.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SensorTab.h" resolved

#include "SensorTab.h"

#include <utility>
#include "ui_SensorTab.h"

SensorTab::SensorTab(QWidget *parent) :
        QWidget(parent), ui(new Ui::SensorTab) {
    ui->setupUi(this);
    iface = new OrgClightClightConfSensorInterface("org.clight.clight", "/org/clight/clight/Conf/Sensor", QDBusConnection::sessionBus(), this);
    monIface = new OrgClightClightConfMonitorOverrideInterface("org.clight.clight", "/org/clight/clight/Conf/MonitorOverride", QDBusConnection::sessionBus(), this);
    bkIface = new OrgClightdClightdBacklightInterface("org.clightd.clightd", "/org/clightd/clightd/Backlight", QDBusConnection::systemBus(), this);

    // Get a list of all serials
    overrides = QMap<QString, MonitorOverride>();
    auto r = monIface->List();
    r.waitForFinished();
    for (const auto&e : r.value()) {
        overrides.insert(e.serial, e);
        ui->overrideComboBox->insertItem(1, e.serial);
    }

    serials = QStringList();
    auto l = bkIface->GetAll("");
    l.waitForFinished();
    for (const auto& e : l.value()) {
        if (!overrides.contains(e.serial))
            serials.append(e.serial);
    }

    if (serials.empty()) {
        ui->addOverrideBtn->setDisabled(true);
    }


    // Create models
    ac = new RegressionPointModel(1, this, iface->acPoints());
    bat = new RegressionPointModel(0, this, iface->battPoints());

    // Create charts
    acGraph = new SensorGraph(this, tr("Display Brightness"), ac);
    batGraph = new SensorGraph(this, tr("Display Brightness"), bat);
    ui->acLayout->layout()->addWidget(acGraph);
    ui->batLayout->layout()->addWidget(batGraph);

    // Connect data changed
    QObject::connect(ac, &RegressionPointModel::dataUpdated, this, &SensorTab::acPointsUpdated);
    QObject::connect(bat, &RegressionPointModel::dataUpdated, this, &SensorTab::batPointsUpdated);

    ui->batSamples->setValue(iface->battCaptures());
    ui->acSamples->setValue(iface->acCaptures());

    // Update dBus on UI
    void (QSpinBox::* qSpinValueChanged)(int) = &QSpinBox::valueChanged;
    QObject::connect(ui->acSamples, qSpinValueChanged, iface, &OrgClightClightConfSensorInterface::setAcCaptures);
    QObject::connect(ui->batSamples, qSpinValueChanged, iface, &OrgClightClightConfSensorInterface::setBattCaptures);

    // Buttons
    QObject::connect(ui->addOverrideBtn, &QToolButton::clicked, this, &SensorTab::addBtnClicked);
    QObject::connect(ui->rmOverrideBtn, &QToolButton::clicked, this, &SensorTab::rmBtnClicked);

    // Dropdown
    void (QComboBox::* qComboIndexChanged)(int) = &QComboBox::currentIndexChanged;
    QObject::connect(ui->overrideComboBox, qComboIndexChanged, this, &SensorTab::serialChanged);
}

SensorTab::~SensorTab() {
    delete ui;

    delete ac;
    delete bat;
}

void SensorTab::addBtnClicked() {
    if (dialog) return;
    if (serials.empty()) return;

    dialog = new AddOverrideDialog(serials, this);
    QObject::connect(dialog, &QDialog::finished, this, &SensorTab::dialogFinished);
    dialog->open();
}

void SensorTab::rmBtnClicked() {
    if (!serial.isEmpty()) {
        auto curSerial = ui->overrideComboBox->currentText();
        monIface->Set(curSerial, SensorFrames(), SensorFrames());
        ui->overrideComboBox->removeItem(boxIndex);

        boxIndex = 0;
        overrides.remove(curSerial);

        serials.append(curSerial);

        ui->addOverrideBtn->setDisabled(false);

        serial = QString();
        ui->overrideComboBox->setCurrentIndex(0);
    }
}

void SensorTab::serialChanged(int index) {
    auto nSerial = ui->overrideComboBox->itemText(index);
    boxIndex = index;
    // the disconnection is probably redundant
    QObject::disconnect(ac, &RegressionPointModel::dataUpdated, this, &SensorTab::acPointsUpdated);
    QObject::disconnect(bat, &RegressionPointModel::dataUpdated, this, &SensorTab::batPointsUpdated);

    if (nSerial == "Default") {
        serial = QString();
        ui->rmOverrideBtn->setDisabled(true);
        ac->resetData(iface->acPoints());
        bat->resetData(iface->battPoints());
    } else {
        serial = nSerial;
        ui->rmOverrideBtn->setDisabled(false);

        auto override = overrides[serial];
        ac->resetData(override.ac);
        bat->resetData(override.bat);
    }

    QObject::connect(ac, &RegressionPointModel::dataUpdated, this, &SensorTab::acPointsUpdated);
    QObject::connect(bat, &RegressionPointModel::dataUpdated, this, &SensorTab::batPointsUpdated);

    if (serials.empty()) ui->addOverrideBtn->setDisabled(true);
}

void SensorTab::acPointsUpdated(QList<double> points) {
    if(serial.isEmpty()) {
        iface->setAcPoints(std::move(points));
    } else {
        MonitorOverride nOverride {
            .serial =  serial,
            .ac = points,
            .bat = bat->getData(),
        };
        monIface->Set(serial, points, nOverride.bat);
        overrides.insert(serial, nOverride);
    }
}

void SensorTab::batPointsUpdated(QList<double> points) {
    if (serial.isEmpty()) {
        iface->setBattPoints(std::move(points));
    } else {
        MonitorOverride nOverride {
                .serial =  serial,
                .ac = ac->getData(),
                .bat = points,
        };
        monIface->Set(serial, nOverride.ac, points);
        overrides.insert(serial, nOverride);
    }
}

void SensorTab::dialogFinished(int code) {
    if (code == 0) {
        dialog->deleteLater();
        dialog = nullptr;
        return;
    }
    serial = dialog->getSelectedSerial();
    serials.removeAll(serial);

    MonitorOverride nOverride {
            .serial =  serial,
            .ac = ac->getData(),
            .bat = bat->getData(),
    };
    monIface->Set(serial, nOverride.ac, nOverride.bat);
    overrides.insert(serial, nOverride);
    ui->overrideComboBox->insertItem(1, serial);
    ui->overrideComboBox->setCurrentIndex(1);

    dialog->deleteLater();
    dialog = nullptr;
}
