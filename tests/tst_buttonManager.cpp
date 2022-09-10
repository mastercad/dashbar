#include "tst_buttonManager.h"

#include "buttonManager.h"
#include "application.h"

#include <QTest>

TestButtonManager::TestButtonManager(QObject *parent)
    : QObject{parent}
{

}

void TestButtonManager::generate() {
    Applications* applications = new Applications();
    ButtonManager* buttonManager = new ButtonManager(applications);
    Application* application = new Application();

    QPushButton* button = buttonManager->generate(application);
}

void TestButtonManager::generate_data() {
    QTest::addColumn<QString>("path");
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("iconPath");
    QTest::addColumn<Applications*>("applications");
    QTest::addColumn<uint>("expectedCount");

    QTest::newRow("single screen resolution") << QRect(0, 0, 1920, 1080) << generateFakeApplicationCollection(0) << QRect(913, 0, 94, 94);
}

Applications* TestButtonManager::generateApplications(QString path) {
    if (!path.isEmpty()) {

    }
}
