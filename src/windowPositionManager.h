#ifndef WINDOWPOSITIONMANAGER_H
#define WINDOWPOSITIONMANAGER_H

#include "applications.h"

#include <QRect>
#include <QMainWindow>

class WindowPositionManager
{
public:
    WindowPositionManager(QMainWindow* mainWindow, Applications* applications);
    void resize(QRect screenGeometry);

private:
    QMainWindow* mainWindow;
    Applications* applications;
};

#endif // WINDOWPOSITIONMANAGER_H
