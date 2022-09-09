#include "tst_windowPositionManager.h"

#include "windowPositionManager.h"
#include "application.h"

#include <QTest>

#include <QRect>
#include <QMainWindow>

TestWindowPositionManager::TestWindowPositionManager(QObject *parent)
    : QObject{parent}
{

}

void TestWindowPositionManager::resize() {
    QFETCH(QRect, screen);
    QFETCH(Applications*, applications);
    QFETCH(QRect, expectation);

    QMainWindow* mainWindow = new QMainWindow();
    WindowPositionManager* windowPositionManager = new WindowPositionManager(mainWindow, applications);

    windowPositionManager->resize(screen);

    QCOMPARE(mainWindow->geometry(), expectation);
}

void TestWindowPositionManager::resize_data() {
    QTest::addColumn<QRect>("screen");
    QTest::addColumn<Applications*>("applications");
    QTest::addColumn<QRect>("expectation");

    QTest::newRow("single screen resolution") << QRect(0, 0, 1920, 1080) << generateFakeApplicationCollection(0) << QRect(913, 0, 94, 94);
    QTest::newRow("one big screen") << QRect(0, 0, 3940, 1080) << generateFakeApplicationCollection(0) << QRect(1923, 0, 94, 94);
    QTest::newRow("two screens, second is primary, resolutions") << QRect(1920, 0, 2560, 1080) << generateFakeApplicationCollection(0) << QRect(3153, 0, 94, 94);

    QTest::newRow("single screen resolution with 3 applications") << QRect(0, 0, 1920, 1080) << generateFakeApplicationCollection(3) << QRect(796, 0, 328, 94);
    QTest::newRow("one big screen with 3 applications") << QRect(0, 0, 3940, 1080) << generateFakeApplicationCollection(3) << QRect(1806, 0, 328, 94);
    QTest::newRow("two screens, second is primary, resolutions with 3 applications") << QRect(1920, 0, 2560, 1080) << generateFakeApplicationCollection(3) << QRect(3036, 0, 328, 94);

    QTest::newRow("single screen resolution with 30 applications") << QRect(0, 0, 1920, 1080) << generateFakeApplicationCollection(30) << QRect(480, 0, 960, 172);
    QTest::newRow("one big screen with 30 applications") << QRect(0, 0, 3940, 1080) << generateFakeApplicationCollection(30) << QRect(1026, 0, 1888, 94);
    QTest::newRow("two screens with different size, second is primary, with 30 applications") << QRect(1920, 0, 2560, 1080) << generateFakeApplicationCollection(30) << QRect(2560, 0, 1280, 172);
    QTest::newRow("two screens, second is primary, with 30 applications") << QRect(1920, 0, 1920, 1080) << generateFakeApplicationCollection(30) << QRect(2400, 0, 960, 172);
}

Applications* TestWindowPositionManager::generateFakeApplicationCollection(uint applicationCount) {
    Applications* applications = new Applications();

    for (uint current = 0; current < applicationCount; ++current) {
        Application* application = new Application();
        application->setPath(&"/Fake/Path/"[current]);
        applications->add(application);
    }

    return applications;
}
