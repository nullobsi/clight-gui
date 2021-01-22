//
// Created by nullobsi on 2021/01/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_TrayMenu.h" resolved

#include "TrayMenu.h"
#include "ui_TrayMenu.h"

TrayMenu::TrayMenu(QWidget *parent) :
        QMenu(parent), ui(new Ui::TrayMenu) {
    ui->setupUi(this);
}

TrayMenu::~TrayMenu() {
    delete ui;
}

Ui::TrayMenu *TrayMenu::getUi() {
    return ui;
}
