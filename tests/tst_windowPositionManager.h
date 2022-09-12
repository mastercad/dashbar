#ifndef TESTWINDOWPOSITIONMANAGER_H
#define TESTWINDOWPOSITIONMANAGER_H

#include "applications.h"

#include <QObject>

class TestWindowPositionManager : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void resize();
    void resize_data();

public:
    explicit TestWindowPositionManager(QObject *parent = nullptr);

private:
    Applications* generateFakeApplicationCollection(uint applicationCount);
};

#endif // TESTWINDOWPOSITIONMANAGER_H
