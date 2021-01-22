#include <QApplication>
#include "gui/MainWindow.h"
#include "util/initializeMetaTypes.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    initializeMetaTypes();
    MainWindow m;
    return QApplication::exec();
}
