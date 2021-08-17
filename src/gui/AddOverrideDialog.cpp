//
// Created by nullobsi on 2021/08/16.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AddOverrideDialog.h" resolved

#include "AddOverrideDialog.h"
#include "ui_AddOverrideDialog.h"


AddOverrideDialog::AddOverrideDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::AddOverrideDialog) {
    ui->setupUi(this);
}

AddOverrideDialog::~AddOverrideDialog() {
    delete ui;
}

AddOverrideDialog::AddOverrideDialog(const QStringList& items, QWidget *parent) :
        QDialog(parent), ui(new Ui::AddOverrideDialog) {
    ui->setupUi(this);
    ui->monitorList->addItems(items);
}

QString AddOverrideDialog::getSelectedSerial() {
    return ui->monitorList->selectedItems().first()->text();
}

