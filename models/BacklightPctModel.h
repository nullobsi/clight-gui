//
// Created by nullobsi on 2021/01/06.
//

#ifndef CLIGHTD_GUI_BACKLIGHTPCTMODEL_H
#define CLIGHTD_GUI_BACKLIGHTPCTMODEL_H
#include <QAbstractTableModel>
#include "SysBacklight.h"
class BacklightPctModel : public QAbstractTableModel {
    Q_OBJECT

public:
    BacklightPctModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

public slots:
    void updated(QString serial, double pct);
private:
    org::clightd::clightd::Backlight *iface;
    BacklightList dat;

    void getData();
};


#endif //CLIGHTD_GUI_BACKLIGHTPCTMODEL_H
