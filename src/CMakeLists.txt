cmake_minimum_required(VERSION 3.17)
project(clight-gui)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets DBus Charts)
set(REQUIRED_LIBS_QUALIFIED Qt${QT_VERSION}::Core Qt${QT_VERSION}::Gui Qt${QT_VERSION}::Widgets Qt${QT_VERSION}::DBus Qt${QT_VERSION}::Charts)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

set(SRC_FILES main.cpp gui/MainWindow.cpp gui/MainWindow.h gui/MainWindow.ui models/BacklightPctModel.cpp models/BacklightPctModel.h util/initializeMetaTypes.cpp util/initializeMetaTypes.h gui/BacklightTab.cpp gui/BacklightTab.h gui/BacklightTab.ui gui/DimmerTab.cpp gui/DimmerTab.h gui/DimmerTab.ui gui/GammaTab.cpp gui/GammaTab.h gui/GammaTab.ui gui/InfoTab.cpp gui/InfoTab.h gui/InfoTab.ui gui/SensorTab.cpp gui/SensorTab.h gui/SensorTab.ui models/RegressionPointModel.cpp models/RegressionPointModel.h gui/KeyboardTab.cpp gui/KeyboardTab.h gui/KeyboardTab.ui gui/ScreenTab.cpp gui/ScreenTab.h gui/ScreenTab.ui gui/DaytimeTab.cpp gui/DaytimeTab.h gui/DaytimeTab.ui gui/TrayMenu.ui gui/TrayMenu.cpp gui/TrayMenu.h dbus/DBusSingle.cpp dbus/DBusSingle.h)

set(CLIGHT_XML dbus/clight/Backlight.xml dbus/clight/clight.xml dbus/clight/Conf.xml dbus/clight/Daytime.xml dbus/clight/Dimmer.xml dbus/clight/Dpms.xml dbus/clight/Gamma.xml dbus/clight/Inhibit.xml dbus/clight/Kbd.xml dbus/clight/Sensor.xml dbus/clight/Screen.xml)
set(CLIGHTD_XML dbus/clightd/Backlight.xml dbus/clightd/Dpms.xml dbus/clightd/Gamma.xml dbus/clightd/Screen.xml dbus/clightd/Sensor.xml)

set(DBUS_FILES)

set(DBUS_TYPE_HEADERS class/BacklightEntry.h class/BacklightSmooth.h class/Coordinate.h class/GammaSmooth.h class/SensorFrames.h)
set(DBUS_TYPE_SOURCES class/BacklightEntry.cpp class/BacklightSmooth.cpp class/Coordinate.cpp class/GammaSmooth.cpp)

foreach(XML_FILE IN LISTS CLIGHT_XML)
    get_filename_component(BASENAME ${XML_FILE} NAME_WE)
    set_source_files_properties(${XML_FILE} PROPERTIES INCLUDE ${CMAKE_SOURCE_DIR}/class/DBusTypes.h NO_NAMESPACE ON)
    qt_add_dbus_interface(DBUS_FILES ${XML_FILE} ${BASENAME})
endforeach()

foreach(XML_FILE IN LISTS CLIGHTD_XML)
    get_filename_component(BASENAME ${XML_FILE} NAME_WE)
    set_source_files_properties(${XML_FILE} PROPERTIES INCLUDE ${CMAKE_SOURCE_DIR}/class/DBusTypes.h NO_NAMESPACE ON)
    qt_add_dbus_interface(DBUS_FILES ${XML_FILE} Sys${BASENAME})
endforeach()

add_executable(${PROJECT_NAME} ${SRC_FILES} ${DBUS_FILES} ${DBUS_TYPE_HEADERS} ${DBUS_TYPE_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
