//
// Created by nullobsi on 2021/01/07.
//

#ifndef CLIGHTD_GUI_GAMMATAB_H
#define CLIGHTD_GUI_GAMMATAB_H

#include <QWidget>
#include "Gamma.h"
#include "SysGamma.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GammaTab; }
QT_END_NAMESPACE

class GammaTab : public QWidget {
Q_OBJECT

public:
    explicit GammaTab(QWidget *parent = nullptr);

    ~GammaTab() override;

public slots:
    void GammaChanged(QString display, int gamma);
    void AmbientGammaChanged(int v);
    void SmoothTransChanged(int v);
    void LongTransChanged(int v);

private:
    Ui::GammaTab *ui;

    QString currDisplay = "";
    QString authority = "";

    // dbus
    OrgClightdClightdGammaInterface *sysGamma;
    OrgClightClightConfGammaInterface *gammaInterface;
};

#endif //CLIGHTD_GUI_GAMMATAB_H
