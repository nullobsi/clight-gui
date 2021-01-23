#include <QApplication>
#include "gui/MainWindow.h"
#include "util/initializeMetaTypes.h"
#include "dbus/DBusSingle.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    initializeMetaTypes();
    auto args = QCoreApplication::arguments();
    // there's probably a better way to do this
    if (args.contains("--help")) {
        qDebug() << "Help:\n--help    Shows help information.\n--tray    Start minimized to tray.";
        exit(0);
    }
    if (QDBusConnection::sessionBus().interface()->isServiceRegistered("org.clightgui")) {
        qDebug() << "Instance is already running. Launching...";
        QDBusInterface *iface = new QDBusInterface("org.clightgui", "/org/clightgui/App", "org.clightgui.App");
        iface->call("ShowWindow");
        exit(0);
    }

    QObject obj;
    DBusSingle *dbus = new DBusSingle(&obj);
    MainWindow m;
    QObject::connect(dbus, &DBusSingle::WindowOpenRequest, &m, &MainWindow::show);
    QDBusConnection::sessionBus().registerObject("/org/clightgui/App", &obj);
    if (!QDBusConnection::sessionBus().registerService("org.clightgui")) {
        qDebug() << "Error creating DBus service:\n" << QDBusConnection::sessionBus().lastError();
        exit(1);
    }
    if (!args.contains("--tray")) {
        m.show();
    }
    return QApplication::exec();
}
