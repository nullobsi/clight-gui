//
// Created by nullobsi on 2021/01/21.
//

#include "RegressionPointModel.h"

#include <utility>


RegressionPointModel::RegressionPointModel(int t, QObject *parent, SensorFrames frames):
        QAbstractListModel(parent),
        dat(){
    type = t;
    beginResetModel();
    dat = std::move(frames);
    endResetModel();
}

int RegressionPointModel::rowCount(const QModelIndex &parent) const {
    return dat.size();
}

QVariant RegressionPointModel::data(const QModelIndex &index, int role) const {
    double value = dat.at(index.row());
    switch(role) {
        case Qt::DisplayRole:
            return QString::number(value*100, 'f', 0) + "%";
        case Qt::EditRole:
            return QString::number(value*100, 'f', 0);
        default:
            return QVariant();
    }
}

QVariant RegressionPointModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role != Qt::DisplayRole) return QVariant();
    return "Brightness";
}

Qt::ItemFlags RegressionPointModel::flags(const QModelIndex &index) const {
    return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
}

bool RegressionPointModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role != Qt::EditRole) return false;

    bool* ok = new bool(false);
    double pct = value.toDouble(ok);
    if (!(*ok)) {
        return false;
    }
    pct = pct / 100;

    dat.replace(index.row(), pct);
    updateData();
    emit dataChanged(index, index);

    return true;
}

void RegressionPointModel::updateData() {
    emit dataUpdated(dat);
}

bool RegressionPointModel::insertRows(int row, int count, const QModelIndex &parent) {
    beginInsertRows(parent, row, row + count - 1);

    for (int i = 0; i < count; i++) {
        dat.insert(row + i, 0.5);
    }
    updateData();

    endInsertRows();

    return true;
}

bool RegressionPointModel::removeRows(int row, int count, const QModelIndex &parent) {
    beginRemoveRows(parent, row, row + count - 1);

    for (int i = 0; i < count; i ++) {
        dat.removeAt(row + i);
    }

    updateData();

    endRemoveRows();
    return true;
}

QList<QPointF> RegressionPointModel::getPoints() {
    auto n = (double)dat.size() - 1;

    QList<QPointF> list = QList<QPointF>();
    for (int i = 0; i < dat.size(); i ++) {
        double v = dat.at(i);
        const auto pt = QPointF(((double)i / n)*100, v*100);
        list.append(pt);
    }

    return list;
}

QList<double> RegressionPointModel::getData() {
    return dat;
}

void RegressionPointModel::resetData(const SensorFrames &f) {
    beginResetModel();
    dat = f;
    endResetModel();
}
