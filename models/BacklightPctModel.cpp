//
// Created by nullobsi on 2021/01/06.
//

#include "BacklightPctModel.h"
#include <QAbstractTableModel>

int BacklightPctModel::rowCount(const QModelIndex &parent) const {
    return dat.count();
}

int BacklightPctModel::columnCount(const QModelIndex &parent) const {
    return 2;
}

BacklightPctModel::BacklightPctModel(QObject *parent) : QAbstractTableModel(parent), dat() {
    iface = new org::clightd::clightd::Backlight("org.clightd.clightd", "/org/clightd/clightd/Backlight", QDBusConnection::systemBus(), this);
    QObject::connect(iface, &org::clightd::clightd::Backlight::Changed, this, &BacklightPctModel::updated);
    getData();
}

QVariant BacklightPctModel::data(const QModelIndex &index, int role) const {
    BacklightEntry s = dat.value(index.row());
    switch(role) {
        case Qt::DisplayRole:
            if (index.column() == 1) {
                return QString::number(s.percent*100, 'f', 0) + "%";
            }
            return s.serial;
        case Qt::EditRole:
            if (index.column() == 1)
                return QString::number(s.percent*100, 'f', 0);
        default:
            return QVariant();
    }
}

QVariant BacklightPctModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role != Qt::DisplayRole) return QVariant();
    if (section == 1) {
        return "Brightness";
    }
    return "Serial";
}

void BacklightPctModel::updated(QString serial, double pct) {
    getData();
}

void BacklightPctModel::getData() {
    beginResetModel();
    QDBusPendingReply<BacklightList> reply = iface->GetAll(nullptr);
    dat = QList(reply.value());
    /*if(reply.isValid()) {

    } else {
        dat = QList<BacklightEntry>();
        const struct BacklightEntry b = {
                reply.error().isValid() ? "Valid" : "Invalid",
                1
        };
        dat.append(b);
    }*/
    endResetModel();
}

Qt::ItemFlags BacklightPctModel::flags(const QModelIndex &index) const {
    qDebug() << index;
    if (index.column() == 1) {
        return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
    }
    return Qt::ItemIsEnabled;
}

bool BacklightPctModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    qDebug() << role;
    if (role != Qt::EditRole) return false;
    if (index.column() != 1) return false;

    auto device = data(index.siblingAtColumn(0)).value<QString>();
    bool* ok = new bool(false);
    double pct = value.toDouble(ok);
    if (!(*ok)) {
        return false;
    }
    pct = pct / 100;
    auto smooth = BacklightSmooth{
        false,
        0,
        0,
    };
    QDBusPendingReply<bool> res = iface->Set(pct, smooth, device);
    return res.value();
}
