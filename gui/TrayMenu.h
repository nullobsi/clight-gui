//
// Created by nullobsi on 2021/01/22.
//

#ifndef CLIGHTD_GUI_TRAYMENU_H
#define CLIGHTD_GUI_TRAYMENU_H

#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class TrayMenu; }
QT_END_NAMESPACE

class TrayMenu : public QMenu {
Q_OBJECT

public:
    explicit TrayMenu(QWidget *parent = nullptr);

    ~TrayMenu() override;
    Ui::TrayMenu *getUi();
private:
    Ui::TrayMenu *ui;
};

#endif //CLIGHTD_GUI_TRAYMENU_H
