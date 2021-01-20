//
// Created by nullobsi on 2021/01/20.
//

// You may need to build the project (run Qt uic code generator) to get "ui_InfoTab.h" resolved

#include "InfoTab.h"
#include "ui_InfoTab.h"

InfoTab::InfoTab(QWidget *parent) :
        QWidget(parent), ui(new Ui::InfoTab) {
    ui->setupUi(this);
}

InfoTab::~InfoTab() {
    delete ui;
}
