//
// Created by nullobsi on 2021/01/01.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

#define CLIGHT "org.clight.clight"
MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    // connect DBus
    clightConf = new OrgClightClightConfInterface(CLIGHT, "/org/clight/clight/Conf", QDBusConnection::sessionBus(), this);
    clight = new OrgClightClightInterface(CLIGHT, "/org/clight/clight", QDBusConnection::sessionBus(), this);
    ui->setupUi(this);
    QDBusMessage introspectCall = QDBusMessage::createMethodCall(CLIGHT, "/org/clight/clight/Conf", "org.freedesktop.DBus.Introspectable", "Introspect");
    QDBusReply<QString> xml = QDBusConnection::sessionBus().call(introspectCall);
    QDomDocument doc;
    doc.setContent(xml);
    QDomElement node = doc.documentElement();
    QDomElement child = node.firstChildElement();
    QSet<QString> enabledModules;
    while (!child.isNull()) {
        if (child.tagName() == "node") {
            enabledModules.insert(child.attribute("name"));
        }
        child = child.nextSiblingElement();
    }
    // load tabs
    tab1 = new InfoTab(this);
    tab2 = new BacklightTab(this);
    tab3 = new DimmerTab(this);
    tab4 = new GammaTab(this);
    tab5 = new SensorTab(this);
    tab6 = new KeyboardTab(this);
    tab7 = new ScreenTab(this);
    tab8 = new DaytimeTab(this);
    int tabN;
    ui->tabWidget->addTab(tab1, tr("Info"));

    tabN = ui->tabWidget->addTab(tab2, tr("Backlight"));
    if (!enabledModules.contains("Backlight")) {
        ui->tabWidget->setTabEnabled(tabN, false);
    }

    tabN = ui->tabWidget->addTab(tab3, tr("Dimmer"));
    if (!enabledModules.contains("Dimmer")){
        ui->tabWidget->setTabEnabled(tabN, false);
    }

    tabN = ui->tabWidget->addTab(tab4, tr("Gamma"));
    if (!enabledModules.contains("Gamma")) {
        ui->tabWidget->setTabEnabled(tabN, false);
    }

    tabN = ui->tabWidget->addTab(tab5, tr("Sensor"));
    if (!enabledModules.contains("Sensor")) {
        ui->tabWidget->setTabEnabled(tabN, false);
    }

    tabN = ui->tabWidget->addTab(tab6, tr("Keyboard"));
    if (!enabledModules.contains("Kbd")) {
        ui->tabWidget->setTabEnabled(tabN, false);
    }

    tabN = ui->tabWidget->addTab(tab7, tr("Screen Comp."));
    if (!enabledModules.contains("Screen")) {
        ui->tabWidget->setTabEnabled(tabN, false);
    }

    tabN = ui->tabWidget->addTab(tab8, tr("Daytime"));
    if (!enabledModules.contains("Daytime")) {
        ui->tabWidget->setTabEnabled(tabN, false);
    }



    tab4->UpdateGamma(clight->temp());

    // update status bar
    clightVer = new QLabel("Clight " + clight->version());
    clightdVer = new QLabel("Clightd " + clight->clightdVersion());
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
    QObject::connect(ui->actionLightTrayIcon, &QAction::triggered, this, &MainWindow::TrayIconChanged);
    ui->actionInhibit->setChecked(clight->inhibited());
    ui->actionLightTrayIcon->setChecked(QSettings().value("light-icons", false).toBool());

    // connect property notifier
    QDBusConnection::sessionBus().connect("org.clight.clight", "/org/clight/clight", "org.freedesktop.DBus.Properties", "PropertiesChanged", this, SLOT(PropertyChanged(QString, QVariantMap)));

    // create tray icon
    trayIcon = new ScrollSysTray(clight->blPct() < 0.5 ? lowBrightness : highBrightness, this);
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
    QObject::connect(trayIcon, &ScrollSysTray::ScrollUp, this, &MainWindow::IncBl);
    QObject::connect(trayIcon, &ScrollSysTray::ScrollDown, this, &MainWindow::DecBl);
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
    TrayIconChanged(QSettings().value("light-icons",false).toBool());
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
                powerState->setText(v.toInt() == 0 ? tr("AC") : tr("Battery"));
            } else if (p == "LidState") {
                lidState->setText(v.toInt() == 0 ? tr("Lid Open") : tr("Lid Closed"));
            } else if (p == "Inhibited") {
                ui->actionInhibit->setChecked(v.toBool());
                trayUi->actionInhibit->setChecked(v.toBool());
            } else if (p == "BlPct") {
                double n = v.toDouble();
                trayUi->menuBacklight->setTitle(tr("Brightness %1\%").arg((int)(n*100)));
                if (n < 0.5) {
                    trayIcon->setIcon(lowBrightness);
                } else {
                    trayIcon->setIcon(highBrightness);
                }
            } else if (p == "AmbientBr") {
                trayUi->actionAmbient->setText(tr("Ambient %1\%").arg((int)(v.toDouble()*100)));
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
            } else if (p == "Temp") {
                tab4->UpdateGamma(v.toInt());
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
	QString str;
	if (inEvent) {
		if (nextEvent) {
			str = tr("Trans. to sunset at %1");
		} else {
			str = tr("Trans. to sunrise at %1");
		}
	} else {
		if (nextEvent) {
			str = tr("Sunset at %1");
		} else {
			str = tr("Sunrise at %1");
		}
	}
    trayUi->labelEventStatus->setText(str.arg(QDateTime::fromSecsSinceEpoch(nextEvent ? sunset : sunrise).toString("H:mm")));
}

void MainWindow::TrayIconChanged(bool lightIcons) {
    QSettings settings;
    settings.setValue("light-icons", lightIcons);
    if (lightIcons) {
        lowBrightness = QIcon::fromTheme("brightness-low-light");
        highBrightness = QIcon::fromTheme("brightness-high-light");
        trayUi->actionDecBl->setIcon(QIcon::fromTheme("brightness-minus-light"));
        trayUi->actionBlInc->setIcon(QIcon::fromTheme("brightness-plus-light"));
    } else {
        lowBrightness = QIcon::fromTheme("brightness-low-dark");
        highBrightness = QIcon::fromTheme("brightness-high-dark");
        trayUi->actionDecBl->setIcon(QIcon::fromTheme("brightness-minus-dark"));
        trayUi->actionBlInc->setIcon(QIcon::fromTheme("brightness-plus-dark"));
    }

    if (clight->blPct() < 0.5) {
        trayIcon->setIcon(lowBrightness);
    } else {
        trayIcon->setIcon(highBrightness);
    }
}
