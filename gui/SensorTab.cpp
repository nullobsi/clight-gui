//
// Created by nullobsi on 2021/01/20.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SensorTab.h" resolved

#include "SensorTab.h"
#include "ui_SensorTab.h"

SensorTab::SensorTab(QWidget *parent) :
        QWidget(parent), ui(new Ui::SensorTab) {
    ui->setupUi(this);

}

SensorTab::~SensorTab() {
    delete ui;
}
