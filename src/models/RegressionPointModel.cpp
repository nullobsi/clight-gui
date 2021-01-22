//
// Created by nullobsi on 2021/01/21.
//

#include "RegressionPointModel.h"

void RegressionPointModel::getData() {
    beginResetModel();
    if (type) {
        dat = iface->acPoints();
    } else {
        dat = iface->battPoints();
    }
    endResetModel();
}

RegressionPointModel::RegressionPointModel(int t, QObject *parent):
        QAbstractListModel(parent),
        dat(){
    type = t;
    iface = new OrgClightClightConfSensorInterface("org.clight.clight", "/org/clight/clight/Conf/Sensor", QDBusConnection::sessionBus(), this);
    getData();
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
    if (type) {
        iface->setAcPoints(dat);
    } else {
        iface->setBattPoints(dat);
    }
}

bool RegressionPointModel::insertRows(int row, int count, const QModelIndex &parent) {
    beginInsertRows(parent, row, row + count - 1);

    for (int i = 0; i < count; i++) {
        dat.insert(i, 0.5);
    }
    updateData();

    endInsertRows();

    return true;
}

bool RegressionPointModel::removeRows(int row, int count, const QModelIndex &parent) {
    beginRemoveRows(parent, row, row + count - 1);

    for (int i = 0; i < count; i ++) {
        dat.removeAt(row);
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

OrgClightClightConfSensorInterface *RegressionPointModel::getIface() {
    return iface;
}
