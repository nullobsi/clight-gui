//
// Created by nullobsi on 2021/01/20.
//

#ifndef CLIGHTD_GUI_INFOTAB_H
#define CLIGHTD_GUI_INFOTAB_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class InfoTab; }
QT_END_NAMESPACE

class InfoTab : public QWidget {
Q_OBJECT

public:
    explicit InfoTab(QWidget *parent = nullptr);

    ~InfoTab() override;

private:
    Ui::InfoTab *ui;
};

#endif //CLIGHTD_GUI_INFOTAB_H
