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
    ui->setupUi(this);
    tab1 = new BacklightTab(this);
    tab2 = new DimmerTab(this);

    ui->tabWidget->addTab(tab1, "Backlight");
    ui->tabWidget->addTab(tab2, "Dimmer");

    QObject::connect(ui->actionSave, &QAction::triggered, this->clightConf, &OrgClightClightConfInterface::Store);

}

MainWindow::~MainWindow() {
    delete ui;
}