//
// Created by nullobsi on 2021/01/21.
//

#ifndef CLIGHTD_GUI_KEYBOARDTAB_H
#define CLIGHTD_GUI_KEYBOARDTAB_H

#include <QWidget>
#include <QLineSeries>
#include "Kbd.h"
#include "../models/RegressionPointModel.h"
#include "SensorGraph.h"

QT_BEGIN_NAMESPACE
namespace Ui { class KeyboardTab; }
QT_END_NAMESPACE

class KeyboardTab : public QWidget {
Q_OBJECT

public:
    explicit KeyboardTab(QWidget *parent = nullptr);

    ~KeyboardTab() override;
public slots:
    void EnabledChecked(int state);

private:
    Ui::KeyboardTab *ui;
    OrgClightClightConfKbdInterface *iface;

    RegressionPointModel *ac;
    RegressionPointModel *bat;

    SensorGraph *acGraph;
    SensorGraph *batGraph;
};

#endif //CLIGHTD_GUI_KEYBOARDTAB_H
