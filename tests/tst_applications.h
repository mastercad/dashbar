#ifndef TESTAPPLICATIONS_H
#define TESTAPPLICATIONS_H

#include <QObject>

class TestApplications : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void get();
    void add();
    void remove();

public:
    explicit TestApplications(QObject *parent = nullptr);

};

#endif // TESTAPPLICATIONS_H
