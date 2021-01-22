//
// Created by nullobsi on 2021/01/01.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    // connect DBus
    clightConf = new OrgClightClightConfInterface("org.clight.clight", "/org/clight/clight/Conf", QDBusConnection::sessionBus(), this);
    clight = new OrgClightClightInterface("org.clight.clight", "/org/clight/clight", QDBusConnection::sessionBus(), this);
    ui->setupUi(this);

    // load tabs
    tab1 = new InfoTab(this);
    tab2 = new BacklightTab(this);
    tab3 = new DimmerTab(this);
    tab4 = new GammaTab(this);
    tab5 = new SensorTab(this);
    tab6 = new KeyboardTab(this);
    tab7 = new ScreenTab(this);
    tab8 = new DaytimeTab(this);

    ui->tabWidget->addTab(tab1, "Info");
    ui->tabWidget->addTab(tab2, "Backlight");
    ui->tabWidget->addTab(tab3, "Dimmer");
    ui->tabWidget->addTab(tab4, "Gamma");
    ui->tabWidget->addTab(tab5, "Sensor");
    ui->tabWidget->addTab(tab6, "Keyboard");
    ui->tabWidget->addTab(tab7, "Screen Comp.");
    ui->tabWidget->addTab(tab8, "Daytime");

    // update status bar
    clightVer = new QLabel("CLight " + clight->version());
    clightdVer = new QLabel("CLightd " + clight->clightdVersion());
    powerState = new QLabel(clight->acState() == 0 ? "AC" : "Battery");
    lidState = new QLabel(clight->lidState() == 0 ? "Lid Open" : "Lid Closed");

    ui->statusbar->addPermanentWidget(clightVer);
    ui->statusbar->addPermanentWidget(clightdVer);
    ui->statusbar->addPermanentWidget(powerState);
    ui->statusbar->addPermanentWidget(lidState);

    // menu options
    QObject::connect(ui->actionSave, &QAction::triggered, this->clightConf, &OrgClightClightConfInterface::Store);
    QObject::connect(ui->storeButton, &QPushButton::clicked, this->clightConf, &OrgClightClightConfInterface::Store);
    QObject::connect(ui->actionCapture, &QAction::triggered, this, &MainWindow::Capture);
    QObject::connect(ui->actionInhibit, &QAction::triggered, this->clight, &OrgClightClightInterface::Inhibit);
    QObject::connect(ui->actionQuit, &QAction::triggered, qApp, &QCoreApplication::quit);
    ui->actionInhibit->setChecked(clight->inhibited());

    // connect property notifier
    QDBusConnection::sessionBus().connect("org.clight.clight", "/org/clight/clight", "org.freedesktop.DBus.Properties", "PropertiesChanged", this, SLOT(PropertyChanged(QString, QVariantMap)));

    // create tray icon
    trayIcon = new QSystemTrayIcon(QIcon::fromTheme("display-brightness"), this);
    trayMenu = new TrayMenu(this);

    trayUi = trayMenu->getUi();

    // mirror Pause option
    // tray -> clight, menu
    // menu -> clight, tray
    QObject::connect(trayUi->actionPause, &QAction::triggered, this->clight, &OrgClightClightInterface::Pause);
    QObject::connect(trayUi->actionPause, &QAction::triggered, ui->actionPause, &QAction::setChecked);

    QObject::connect(ui->actionPause, &QAction::triggered, this->clight, &OrgClightClightInterface::Pause);
    QObject::connect(ui->actionPause, &QAction::triggered, trayUi->actionPause, &QAction::setChecked);

    // connect tray actions
    QObject::connect(trayUi->actionInhibit, &QAction::triggered, this->clight, &OrgClightClightInterface::Inhibit);
    QObject::connect(trayUi->actionCapture, &QAction::triggered, this, &MainWindow::Capture);
    QObject::connect(trayUi->actionQuit, &QAction::triggered, qApp, &QCoreApplication::quit);
    QObject::connect(trayUi->actionBlInc, &QAction::triggered, this, &MainWindow::IncBl);
    QObject::connect(trayUi->actionDecBl, &QAction::triggered, this, &MainWindow::DecBl);
    QObject::connect(trayUi->actionAutoCalib, &QAction::triggered, this, &MainWindow::MenuAutoCalibChanged);
    QObject::connect(tab2, &BacklightTab::AutoCalibChanged, trayUi->actionAutoCalib, &QAction::setChecked);
    QObject::connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::TrayIconActivated);

    trayUi->actionInhibit->setChecked(clight->inhibited());
    trayUi->actionAutoCalib->setChecked(tab2->AutoCalib());

    trayUi->menuBacklight->setTitle("Brightness " + QString::number((int)(clight->blPct()*100)) + "%");
    trayUi->actionAmbient->setText("Ambient " + QString::number((int)(clight->ambientBr()*100)) + "%");

    trayIcon->setContextMenu(trayMenu);
    trayIcon->setVisible(true);

    inEvent = clight->inEvent();
    sunrise = clight->sunrise();
    sunset = clight->sunset();
    nextEvent = clight->nextEvent();
    UpdateTray();
}

MainWindow::~MainWindow() {
    delete ui;
    delete tab1;
    delete tab2;
    delete tab3;
    delete tab4;
    delete trayIcon;
    delete trayMenu;
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
                trayUi->actionInhibit->setChecked(v.toBool());
            } else if (p == "BlPct") {
                trayUi->menuBacklight->setTitle("Brightness " + QString::number((int)(v.toDouble()*100)) + "%");
            } else if (p == "AmbientBr") {
                trayUi->actionAmbient->setText("Ambient " + QString::number((int)(v.toDouble()*100)) + "%");
            } else if (p == "Sunrise") {
                sunrise = v.toULongLong();
                UpdateTray();
            } else if (p == "Sunset") {
                sunset = v.toULongLong();
                UpdateTray();
            } else if (p == "NextEvent") {
                nextEvent = v.toInt();
                UpdateTray();
            } else if (p == "InEvent") {
                inEvent = v.toBool();
                UpdateTray();
            }
        }
    }
}

void MainWindow::Capture(bool checked) {
    clight->Capture(false, false);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    }
}

void MainWindow::DecBl() {
    clight->DecBl(0.05);
}

void MainWindow::IncBl() {
    clight->IncBl(0.05);
}

void MainWindow::MenuAutoCalibChanged(bool v) {
    emit tab2->autoCalibChanged(v ? 2 : 0);
}

void MainWindow::TrayIconActivated(QSystemTrayIcon::ActivationReason reason) {
    switch (reason) {
        case QSystemTrayIcon::Trigger:
            if (this->isVisible()) {
                this->hide();
            } else {
                this->show();
            }
            break;
        default:
            break;
    }
}

void MainWindow::UpdateTray() {
    auto str = QString("%1%2 at %3")
            .arg(inEvent ? "Trans. to " : "")
            .arg(nextEvent ? "Sunset" : "Sunrise")
            .arg(QDateTime::fromSecsSinceEpoch(nextEvent ? sunset : sunrise).toString("H:mm"));
    trayUi->labelEventStatus->setText(str);
}
