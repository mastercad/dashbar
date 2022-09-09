#include "windowPositionManager.h"

#include <math.h>

WindowPositionManager::WindowPositionManager(QMainWindow* mainWindow, Applications* applications): mainWindow(mainWindow), applications(applications)
{

}

void WindowPositionManager::resize(QRect screenGeometry) {
    int buttonSize = 78;
    int margins = 16;

    int applicationCount = applications->getData()->count() + 1;
    int maxWidth = screenGeometry.width() / 2;
    int newWidth = (applicationCount * buttonSize) + margins;
    int newHeight = buttonSize + margins;
    int applicationMaxCountPerRow = (maxWidth - margins) / buttonSize;
    float faktor = ceil((float) applicationCount / applicationMaxCountPerRow);

    if (newWidth > maxWidth) {
        newWidth = maxWidth;
        newHeight = (faktor * buttonSize) + margins;
    }

    int newLeft = screenGeometry.left() + (screenGeometry.width() / 2) - (newWidth / 2);
    QRect newGeometry(newLeft, 0, newLeft + newWidth, newHeight);

    mainWindow->setGeometry(newGeometry);
    mainWindow->setMaximumSize(QSize(newWidth, newHeight));
    mainWindow->setFixedSize(QSize(newWidth, newHeight));
}
