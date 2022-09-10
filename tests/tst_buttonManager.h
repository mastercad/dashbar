#ifndef TESTBUTTONMANAGER_H
#define TESTBUTTONMANAGER_H

#include "applications.h"

#include <QObject>

class TestButtonManager : public QObject
{
    Q_OBJECT

private slots:
    void generate();
    void generate_data();

public:
    explicit TestButtonManager(QObject *parent = nullptr);

signals:

private:
    Applications* generateApplications(QString path = "");
};

#endif // TESTBUTTONMANAGER_H
