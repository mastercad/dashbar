#include "osretriever.h"

#include <QSysInfo>

#include <QDebug>

QString OSRetriever::retrieve()
{
    QString kernelType = QSysInfo::kernelType();
    QString productVersion = QSysInfo::productVersion();

    qDebug() << "kernelType: " << kernelType;
    qDebug() << "Product Version: " << productVersion;

    if ("linux" == kernelType) {
        qDebug() << "LINUX ERKANNT!";
        return "linux";
    }

    if ("windows" == productVersion) {
        qDebug() << "WINDOWS ERKANNT!";
        return "windows";
    }

    if ("macOS" == productVersion) {
        qDebug() << "MAC OS ERKANNT!";
        return "mac-os";
    }

    return "";
}
