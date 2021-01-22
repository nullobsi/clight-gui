#include <QApplication>
#include "gui/MainWindow.h"
#include "util/initializeMetaTypes.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    initializeMetaTypes();
    auto args = QCoreApplication::arguments();
    // there's probably a better way to do this
    if (args.contains("--help")) {
        qDebug() << "Help:\n--help    Shows help information.\n--tray    Start minimized to tray.";
        return 0;
    }
    MainWindow m;
    if (!args.contains("--tray")) {
        m.show();
    }
    return QApplication::exec();
}
