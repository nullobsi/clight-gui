cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0071 NEW)

if (NOT DEFINED CMAKE_INSTALL_PREFIX)
    set (CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "Install to /usr" FORCE)
endif()

project(clight-gui)

option(GENERATE_TRANSLATIONS off "Generate translations for other languages.")

configure_file(${CMAKE_SOURCE_DIR}/resources/translations.qrc ${CMAKE_BINARY_DIR} COPYONLY)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets DBus Charts Xml)
set(REQUIRED_LIBS_QUALIFIED Qt${QT_VERSION}::Core Qt${QT_VERSION}::Gui Qt${QT_VERSION}::Widgets Qt${QT_VERSION}::DBus Qt${QT_VERSION}::Charts Qt${QT_VERSION}::Xml)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

set(SRC_FILES main.cpp gui/MainWindow.cpp gui/MainWindow.h gui/MainWindow.ui models/BacklightPctModel.cpp models/BacklightPctModel.h util/initializeMetaTypes.cpp util/initializeMetaTypes.h gui/BacklightTab.cpp gui/BacklightTab.h gui/BacklightTab.ui gui/DimmerTab.cpp gui/DimmerTab.h gui/DimmerTab.ui gui/GammaTab.cpp gui/GammaTab.h gui/GammaTab.ui gui/InfoTab.cpp gui/InfoTab.h gui/InfoTab.ui gui/SensorTab.cpp gui/SensorTab.h gui/SensorTab.ui models/RegressionPointModel.cpp models/RegressionPointModel.h gui/KeyboardTab.cpp gui/KeyboardTab.h gui/KeyboardTab.ui gui/ScreenTab.cpp gui/ScreenTab.h gui/ScreenTab.ui gui/DaytimeTab.cpp gui/DaytimeTab.h gui/DaytimeTab.ui gui/TrayMenu.ui gui/TrayMenu.cpp gui/TrayMenu.h dbus/DBusSingle.cpp dbus/DBusSingle.h class/ScrollSysTray.cpp class/ScrollSysTray.h gui/SensorGraph.cpp gui/SensorGraph.h gui/SensorGraph.ui gui/AddOverrideDialog.cpp gui/AddOverrideDialog.h gui/AddOverrideDialog.ui)

set(CLIGHT_XML dbus/clight/Backlight.xml dbus/clight/clight.xml dbus/clight/Conf.xml dbus/clight/Daytime.xml dbus/clight/Dimmer.xml dbus/clight/Dpms.xml dbus/clight/Gamma.xml dbus/clight/Inhibit.xml dbus/clight/Kbd.xml dbus/clight/Sensor.xml dbus/clight/Screen.xml dbus/clight/MonitorOverride.xml)
set(CLIGHTD_XML dbus/clightd/Backlight.xml dbus/clightd/Dpms.xml dbus/clightd/Gamma.xml dbus/clightd/Screen.xml dbus/clightd/Sensor.xml)

set(DBUS_FILES)

set(DBUS_TYPE_HEADERS class/BacklightEntry.h class/BacklightSmooth.h class/Coordinate.h class/GammaSmooth.h class/SensorFrames.h class/MonitorOverride.h)
set(DBUS_TYPE_SOURCES class/BacklightEntry.cpp class/BacklightSmooth.cpp class/Coordinate.cpp class/GammaSmooth.cpp class/MonitorOverride.cpp)

if (GENERATE_TRANSLATIONS)
    find_package(Qt${QT_VERSION} COMPONENTS LinguistTools REQUIRED)
    if (${QT_VERSION} EQUAL 5)
        qt5_create_translation(QM_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/localization/clight-gui_en.ts ${CMAKE_SOURCE_DIR}/localization/clight-gui_ja.ts)
    else()
        qt6_create_translation(QM_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/localization/clight-gui_en.ts ${CMAKE_SOURCE_DIR}/localization/clight-gui_ja.ts)
    endif()
    list(APPEND SRC_FILES ${QM_FILES} ${CMAKE_BINARY_DIR}/translations.qrc)
endif()

foreach(XML_FILE IN LISTS CLIGHT_XML)
    get_filename_component(BASENAME ${XML_FILE} NAME_WE)
    set_source_files_properties(${XML_FILE} PROPERTIES INCLUDE ${CMAKE_SOURCE_DIR}/class/DBusTypes.h NO_NAMESPACE ON)
    if (${QT_VERSION} EQUAL 5)
        qt5_add_dbus_interface(DBUS_FILES ${XML_FILE} ${BASENAME})
    else()
        qt6_add_dbus_interface(DBUS_FILES ${XML_FILE} ${BASENAME})
    endif()
endforeach()

foreach(XML_FILE IN LISTS CLIGHTD_XML)
    get_filename_component(BASENAME ${XML_FILE} NAME_WE)
    set_source_files_properties(${XML_FILE} PROPERTIES INCLUDE ${CMAKE_SOURCE_DIR}/class/DBusTypes.h NO_NAMESPACE ON)
    if (${QT_VERSION} EQUAL 5)
        qt5_add_dbus_interface(DBUS_FILES ${XML_FILE} Sys${BASENAME})
    else()
        qt6_add_dbus_interface(DBUS_FILES ${XML_FILE} Sys${BASENAME})
    endif()
endforeach()

add_executable(${PROJECT_NAME} ${SRC_FILES} ${DBUS_FILES} ${DBUS_TYPE_HEADERS} ${DBUS_TYPE_SOURCES} ${QM_FILES} resources/resources.qrc)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

install(TARGETS ${PROJECT_NAME} RUNTIME)

set(ICONDIR "resources/icons")
set(ICONS ${ICONDIR}/brightness-high-dark.svg ${ICONDIR}/brightness-high-light.svg
          ${ICONDIR}/brightness-low-dark.svg ${ICONDIR}/brightness-low-light.svg
          ${ICONDIR}/brightness-minus-dark.svg ${ICONDIR}/brightness-minus-light.svg
          ${ICONDIR}/brightness-plus-dark.svg ${ICONDIR}/brightness-plus-light.svg)

install(FILES ${ICONS} DESTINATION "share/icons/hicolor/scalable/status")

# Get the current working branch
find_program(GITBIN git)
if(NOT DEFINED RELVER)
    if (DEFINED GITBIN AND EXISTS ${CMAKE_SOURCE_DIR}/../.git)
        execute_process(
            COMMAND git rev-list --count HEAD
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_REVISION
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )

        # Get the latest abbreviated commit hash of the working branch
        execute_process(
            COMMAND git rev-parse --short HEAD
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_COMMIT_HASH
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )

        set(RELVER "r${GIT_REVISION}.${GIT_COMMIT_HASH}")
    else()
        set(RELVER "build-local")
    endif()
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE RELVER=\"${RELVER}\")