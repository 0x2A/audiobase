#include "mainwindow.h"
#include <QApplication>
#include <QLibraryInfo>
#include <QTranslator>
#include "common.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setApplicationName(AB_NAME);
    QApplication::setOrganizationName(AB_ORGANIZATION_NAME);
    QApplication::setApplicationDisplayName(AB_DISPLAY_NAME);
    QApplication::setApplicationVersion(AB_VERSION);

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
                QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    QTranslator myappTranslator;
        myappTranslator.load("audiobase_" + QLocale::system().name());
        a.installTranslator(&myappTranslator);

    MainWindow w;
    w.show();

    return a.exec();
}
