//
// Created by nullobsi on 2021/01/01.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    clightConf = new OrgClightClightConfInterface("org.clight.clight", "/org/clight/clight/Conf", QDBusConnection::sessionBus(), this);
    clight = new OrgClightClightInterface("org.clight.clight", "/org/clight/clight", QDBusConnection::sessionBus(), this);
    ui->setupUi(this);

    tab1 = new InfoTab(this);
    tab2 = new BacklightTab(this);
    tab3 = new DimmerTab(this);
    tab4 = new GammaTab(this);
    tab5 = new SensorTab(this);
    tab6 = new KeyboardTab(this);

    ui->tabWidget->addTab(tab1, "Info");
    ui->tabWidget->addTab(tab2, "Backlight");
    ui->tabWidget->addTab(tab3, "Dimmer");
    ui->tabWidget->addTab(tab4, "Gamma");
    ui->tabWidget->addTab(tab5, "Sensor");
    ui->tabWidget->addTab(tab6, "Keyboard");


    clightVer = new QLabel("CLight " + clight->version());
    clightdVer = new QLabel("CLightd " + clight->clightdVersion());
    powerState = new QLabel(clight->acState() == 0 ? "AC" : "Battery");
    lidState = new QLabel(clight->lidState() == 0 ? "Lid Open" : "Lid Closed");
    ui->actionInhibit->setChecked(clight->inhibited());

    ui->statusbar->addPermanentWidget(clightVer);
    ui->statusbar->addPermanentWidget(clightdVer);
    ui->statusbar->addPermanentWidget(powerState);
    ui->statusbar->addPermanentWidget(lidState);

    QObject::connect(ui->actionSave, &QAction::triggered, this->clightConf, &OrgClightClightConfInterface::Store);
    QObject::connect(ui->actionCapture, &QAction::triggered, this, &MainWindow::Capture);
    QObject::connect(ui->actionInhibit, &QAction::triggered, this->clight, &OrgClightClightInterface::Inhibit);
    QObject::connect(ui->actionPause, &QAction::triggered, this->clight, &OrgClightClightInterface::Pause);
    QDBusConnection::sessionBus().connect("org.clight.clight", "/org/clight/clight", "org.freedesktop.DBus.Properties", "PropertiesChanged", this, SLOT(PropertyChanged(QString, QVariantMap)));

}

MainWindow::~MainWindow() {
    delete ui;
    delete tab1;
    delete tab2;
    delete tab3;
    delete tab4;
}

void MainWindow::PropertyChanged(QString interface, QVariantMap propertiesUpdated) {
    if (interface == "org.clight.clight") {
        auto keys = propertiesUpdated.keys();
        for (const QString &p : keys) {
            const QVariant v = propertiesUpdated.value(p);
            if (p == "AcState") {
                powerState->setText(v.toInt() == 0 ? "AC" : "Battery");
            } else if (p == "LidState") {
                lidState->setText(v.toInt() == 0 ? "Lid Open" : "Lid Closed");
            } else if (p == "Inhibited") {
                ui->actionInhibit->setChecked(v.toBool());
            }
        }
    }
}

void MainWindow::Capture(bool checked) {
    clight->Capture(false, false);
}
