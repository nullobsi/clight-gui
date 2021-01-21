//
// Created by nullobsi on 2021/01/06.
//

#include "../class/DBusTypes.h"

void initializeMetaTypes() {
    qDBusRegisterMetaType<SensorFrames>();
    qDBusRegisterMetaType<Coordinate>();
    qDBusRegisterMetaType<BacklightSmooth>();
    qDBusRegisterMetaType<GammaSmooth>();
    qDBusRegisterMetaType<BacklightList>();
    qDBusRegisterMetaType<BacklightEntry>();
//    qDBusRegisterMetaType<PropertiesStruct>();
//qDBusRegisterMetaType<PropertiesList>();

}