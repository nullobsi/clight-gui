#include <QApplication>
#include "gui/MainWindow.h"
#include "util/initializeMetaTypes.h"
#include "dbus/DBusSingle.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);// check icon theme
	QCoreApplication::setOrganizationName("clight-gui");
	QCoreApplication::setApplicationName("clight-gui");
	QCoreApplication::setApplicationVersion(RELVER);

    initializeMetaTypes();

    QTranslator t;
    t.load(QLocale::system(), "qtbase_");
    t.load(QLocale::system(), "clight-gui_", QString(), ":/translations");
    a.installTranslator(&t);

    QCommandLineParser parser;
    parser.setApplicationDescription("Clight GUI");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption trayOption("tray", QCoreApplication::translate("main", "Start minimized to tray."));
    parser.addOption(trayOption);

    parser.process(a);

    if (QDBusConnection::sessionBus().interface()->isServiceRegistered("org.clightgui")) {
        qDebug() << "Instance is already running. Launching...";
        QDBusInterface *iface = new QDBusInterface("org.clightgui", "/org/clightgui/App", "org.clightgui.App");
        iface->call("ShowWindow");
        exit(0);
    }

    // initialize DBus service
    QObject obj;
    DBusSingle *dbus = new DBusSingle(&obj);
    QDBusConnection::sessionBus().registerObject("/org/clightgui/App", &obj);
    if (!QDBusConnection::sessionBus().registerService("org.clightgui")) {
        qDebug() << "Error creating DBus service:\n" << QDBusConnection::sessionBus().lastError();
        exit(1);
    }

    QStringList search;
    search << ":/icons";
    QIcon::setFallbackSearchPaths(search);

    // initialize main window
    MainWindow m;
    QObject::connect(dbus, &DBusSingle::WindowOpenRequest, &m, &MainWindow::show);
    QSettings sett;
    if (!sett.allKeys().contains("start-in-tray")) {
        sett.setValue("start-in-tray", QVariant(false));
    }
    if (!parser.isSet(trayOption) && !sett.value("start-in-tray", QVariant(false)).toBool()) {
        m.show();
    }
    return QApplication::exec();
}
