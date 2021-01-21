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

    ui->tabWidget->addTab(tab1, "Info");
    ui->tabWidget->addTab(tab2, "Backlight");
    ui->tabWidget->addTab(tab3, "Dimmer");
    ui->tabWidget->addTab(tab4, "Gamma");
    ui->tabWidget->addTab(tab5, "Sensor");

    // TODO: use freedesktop properties interface to update when status changes
    clightVer = new QLabel("CLight " + clight->version());
    clightdVer = new QLabel("CLightd " + clight->clightdVersion());
    powerState = new QLabel(clight->acState() == 0 ? "AC" : "Battery");
    lidState = new QLabel(clight->lidState() == 0 ? "Lid Open" : "Lid Closed");

    ui->statusbar->addPermanentWidget(clightVer);
    ui->statusbar->addPermanentWidget(clightdVer);
    ui->statusbar->addPermanentWidget(powerState);
    ui->statusbar->addPermanentWidget(lidState);

    QObject::connect(ui->actionSave, &QAction::triggered, this->clightConf, &OrgClightClightConfInterface::Store);

}

MainWindow::~MainWindow() {
    delete ui;
    delete tab1;
    delete tab2;
    delete tab3;
    delete tab4;
}