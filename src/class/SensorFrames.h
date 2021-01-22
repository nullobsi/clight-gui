//
// Created by nullobsi on 2021/01/06.
//

#ifndef CLIGHTD_GUI_SENSORFRAMES_H
#define CLIGHTD_GUI_SENSORFRAMES_H
#include <QList>
#include <QtDBus/qdbusmetatype.h>

typedef QList<double> SensorFrames;
Q_DECLARE_METATYPE(SensorFrames);

#endif //CLIGHTD_GUI_SENSORFRAMES_H
