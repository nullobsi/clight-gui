//
// Created by nullobsi on 2021/01/01.
//

#ifndef CLIGHTD_GUI_MAINWINDOW_H
#define CLIGHTD_GUI_MAINWINDOW_H

#include <QMainWindow>
#include "BacklightTab.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

    BacklightTab *tab1;
};

#endif //CLIGHTD_GUI_MAINWINDOW_H
