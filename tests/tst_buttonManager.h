#ifndef TESTBUTTONMANAGER_H
#define TESTBUTTONMANAGER_H

#include "applications.h"

#include <QObject>

class TestButtonManager : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void generate();
    void generate_data();

public:
    explicit TestButtonManager(QObject *parent = nullptr);

signals:

private:
    Applications* generateFakeApplicationCollection(uint applicationCount);
};

#endif // TESTBUTTONMANAGER_H
