//
// Created by nullobsi on 2021/01/22.
//

#include "DBusSingle.h"

DBusSingle::DBusSingle(QObject *parent) : QDBusAbstractAdaptor(parent) {

}

[[maybe_unused]] void DBusSingle::ShowWindow() {
    emit WindowOpenRequest();
}
