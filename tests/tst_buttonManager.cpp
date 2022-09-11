#include "tst_buttonManager.h"

#include "buttonManager.h"
#include "application.h"

#include <QTest>

#include <QSize>

class ButtonManagerMock: public ButtonManager
{
public:
    ButtonManagerMock(Applications* applications): ButtonManager(applications) {};
    QHash<QString, QPushButton*>* getButtons() const { return buttons; };
    QSignalMapper* getSignalMapper() const { return signalMapper; };
};

TestButtonManager::TestButtonManager(QObject *parent)
    : QObject{parent}
{

}

void TestButtonManager::generate() {
    QFETCH(QString, path);
    QFETCH(QString, name);
    QFETCH(QString, iconPath);
    QFETCH(int, expectedButtonCount);

    Applications* applications = new Applications();
    ButtonManagerMock* buttonManager = new ButtonManagerMock(applications);

    Application* application = new Application();
    application->setPath(path)
        ->setName(name)
        ->setIcon(iconPath);

    QPushButton* button = buttonManager->generate(application);

    QCOMPARE(button->iconSize(), QSize(64, 64));
    QCOMPARE(buttonManager->getButtons()->count(), expectedButtonCount);

    if (expectedButtonCount) {
        QCOMPARE(buttonManager->getButtons()->find(application->getPath()).value(), button);
    } else {
        QCOMPARE(buttonManager->getButtons()->isEmpty(), true);
    }
}

void TestButtonManager::generate_data() {
    QTest::addColumn<QString>("path");
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("iconPath");
    QTest::addColumn<int>("expectedButtonCount");

    QTest::newRow("add application with path") << "/path/to/executable" << "first app" << "/path/to/icon" << 1;
    QTest::newRow("add application without path") << "" << "second first app" << "/path/to/icon" << 0;
}

Applications* TestButtonManager::generateFakeApplicationCollection(uint applicationCount) {
    Applications* applications = new Applications();

    for (uint current = 0; current < applicationCount; ++current) {
        Application* application = new Application();
        application->setPath(&"/Fake/Path/"[current]);
        applications->add(application);
    }

    return applications;
}
