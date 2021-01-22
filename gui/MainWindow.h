//
// Created by nullobsi on 2021/01/01.
//

#ifndef CLIGHTD_GUI_MAINWINDOW_H
#define CLIGHTD_GUI_MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "BacklightTab.h"
#include "DimmerTab.h"
#include "Conf.h"
#include "GammaTab.h"
#include "InfoTab.h"
#include "SensorTab.h"
#include "KeyboardTab.h"
#include "ScreenTab.h"
#include "DaytimeTab.h"
#include "clight.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

public slots:
    void PropertyChanged(QString interface, QVariantMap propertiesUpdated);
    void Capture(bool checked);
private:
    Ui::MainWindow *ui;
    OrgClightClightConfInterface *clightConf;
    OrgClightClightInterface *clight;

    // tabs
    InfoTab *tab1;
    BacklightTab *tab2;
    DimmerTab *tab3;
    GammaTab *tab4;
    SensorTab *tab5;
    KeyboardTab *tab6;
    ScreenTab *tab7;
    DaytimeTab *tab8;


    //status bar info
    QLabel *powerState;
    QLabel *lidState;
    QLabel *clightVer;
    QLabel *clightdVer;
};

#endif //CLIGHTD_GUI_MAINWINDOW_H
