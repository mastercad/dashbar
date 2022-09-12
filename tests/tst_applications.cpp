#include "tst_applications.h"

#include "applications.h"
#include "application.h"

#include <QTest>

TestApplications::TestApplications(QObject *parent) : QObject{parent}
{

}

void TestApplications::get() {
    Applications* applications = new Applications();
    Application* application = new Application();
    application->setPath("/my/application/path");
    applications->add(application);

    QCOMPARE(applications->get("/my/application/path"), application);
    QCOMPARE(applications->getData()->count(), 1);
}

void TestApplications::add() {
    Applications* applications = new Applications();
    Application* application1 = new Application();
    application1->setPath("/my/application/path1");
    applications->add(application1);

    Application* application2 = new Application();
    application2->setPath("/my/application/path2");
    applications->add(application2);

    Application* application3 = new Application();
    application3->setPath("/my/application/path3");
    applications->add(application3);

    Application* application4 = new Application();
    application4->setPath("/my/application/path2");
    applications->add(application4);

    QCOMPARE(applications->get("/my/application/path1"), application1);
    QCOMPARE(applications->get("/my/application/path2"), application4);
    QCOMPARE(applications->get("/my/application/path3"), application3);
    QCOMPARE(applications->getData()->count(), 3);
}

void TestApplications::remove() {
    Applications* applications = new Applications();
    Application* application1 = new Application();
    application1->setPath("/my/application/path1");
    applications->add(application1);

    Application* application2 = new Application();
    application2->setPath("/my/application/path2");
    applications->add(application2);

    Application* application3 = new Application();
    application3->setPath("/my/application/path3");
    applications->add(application3);

    applications->remove("/my/application/path2");

    QCOMPARE(applications->get("/my/application/path1"), application1);
    QCOMPARE(applications->get("/my/application/path2"), nullptr);
    QCOMPARE(applications->get("/my/application/path3"), application3);
    QCOMPARE(applications->getData()->count(), 2);
}
