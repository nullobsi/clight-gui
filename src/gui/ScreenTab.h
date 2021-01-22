//
// Created by nullobsi on 2021/01/21.
//

#ifndef CLIGHTD_GUI_SCREENTAB_H
#define CLIGHTD_GUI_SCREENTAB_H

#include <QWidget>
#include "Screen.h"
QT_BEGIN_NAMESPACE
namespace Ui { class ScreenTab; }
QT_END_NAMESPACE

class ScreenTab : public QWidget {
Q_OBJECT

public:
    explicit ScreenTab(QWidget *parent = nullptr);

    ~ScreenTab() override;

private:
    Ui::ScreenTab *ui;
    OrgClightClightConfScreenInterface *iface;
};

#endif //CLIGHTD_GUI_SCREENTAB_H
