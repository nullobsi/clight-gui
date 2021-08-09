//
// Created by nullobsi on 2021/01/21.
//

#ifndef CLIGHTD_GUI_REGRESSIONPOINTMODEL_H
#define CLIGHTD_GUI_REGRESSIONPOINTMODEL_H
#include <QAbstractListModel>
#include "QPointF"
#include "../class/SensorFrames.h"

class RegressionPointModel : public QAbstractListModel {
    Q_OBJECT



public:
    explicit RegressionPointModel(int t, QObject *parent, SensorFrames frames);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    QList<QPointF> getPoints();

signals:
    void dataUpdated(SensorFrames);

private:
    QList<double> dat;

    int type;
    void updateData();
};


#endif //CLIGHTD_GUI_REGRESSIONPOINTMODEL_H
