//
// Created by nullobsi on 2021/01/01.
//

#ifndef CLIGHTD_GUI_MAINWINDOW_H
#define CLIGHTD_GUI_MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSystemTrayIcon>
#include "../class/ScrollSysTray.h"
#include "BacklightTab.h"
#include "DimmerTab.h"
#include "Conf.h"
#include "GammaTab.h"
#include "InfoTab.h"
#include "SensorTab.h"
#include "KeyboardTab.h"
#include "ScreenTab.h"
#include "DaytimeTab.h"
#include "TrayMenu.h"
#include "ui_TrayMenu.h"
#include "clight.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void PropertyChanged(QString interface, QVariantMap propertiesUpdated);
    void Capture(bool checked);

    void IncBl();
    void DecBl();

    void MenuAutoCalibChanged(bool v);
    void TrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void TrayIconChanged(bool lightIcons);
private:
    Ui::MainWindow *ui;
    ScrollSysTray *trayIcon;
    TrayMenu *trayMenu;
    Ui::TrayMenu *trayUi;
    QIcon lowBrightness = QIcon::fromTheme("brightness-low"/*, QIcon(":/icons/dark/brightness-low.svg")*/);
    QIcon highBrightness = QIcon::fromTheme("brightness-high"/*, QIcon(":/icons/dark/brightness-high.svg")*/);

    // DBus
    OrgClightClightConfInterface *clightConf;
    OrgClightClightInterface *clight;

    // Tabs
    InfoTab *tab1;
    BacklightTab *tab2;
    DimmerTab *tab3;
    GammaTab *tab4;
    SensorTab *tab5;
    KeyboardTab *tab6;
    ScreenTab *tab7;
    DaytimeTab *tab8;

    // Status bar info
    QLabel *powerState;
    QLabel *lidState;
    QLabel *clightVer;
    QLabel *clightdVer;

    // String for tray
    int nextEvent;
    bool inEvent;
    qulonglong sunrise;
    qulonglong sunset;
    void UpdateTray();

};

#endif //CLIGHTD_GUI_MAINWINDOW_H
