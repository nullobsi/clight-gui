//
// Created by nullobsi on 2021/08/16.
//

#ifndef CLIGHT_GUI_ADDOVERRIDEDIALOG_H
#define CLIGHT_GUI_ADDOVERRIDEDIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class AddOverrideDialog; }
QT_END_NAMESPACE

class AddOverrideDialog : public QDialog {
Q_OBJECT

public:
    explicit AddOverrideDialog(QWidget *parent = nullptr);
    explicit AddOverrideDialog(const QStringList& items, QWidget *parent = nullptr);

    ~AddOverrideDialog() override;

    QString getSelectedSerial();

private:
    Ui::AddOverrideDialog *ui;
};


#endif //CLIGHT_GUI_ADDOVERRIDEDIALOG_H
