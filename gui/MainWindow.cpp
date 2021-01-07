//
// Created by nullobsi on 2021/01/01.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Backlight.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {

    ui->setupUi(this);
    tab1 = new BacklightTab(this);
    ui->tabWidget->addTab(tab1, "Backlight");

}

MainWindow::~MainWindow() {
    delete ui;
}