#ifndef QT_NO_SYSTEMTRAYICON

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QMessageBox>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);

    QApplication app(argc, argv);

    app.setOrganizationName("ByteArtist");
    app.setOrganizationDomain("byte-artist.de");
    app.setApplicationName("Dashboard");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Dashbar_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(nullptr, QObject::tr("Systray"), QObject::tr("I couldn't detect any system tray on this system."));
        return 1;
    }

    QApplication::setQuitOnLastWindowClosed(false);

    MainWindow window;
    window.move(QPoint(window.geometry().left(), -94));
    window.show();

    return app.exec();
}

#else

#include <QLabel>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString text("QSystemTrayIcon is not supported on this platform");

    QLabel *label = new QLabel(text);
    label->setWordWrap(true);

    label->show();
    qDebug() << text;

    app.exec();
}

#endif
