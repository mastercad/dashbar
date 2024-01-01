#include "osretriever.h"

#include <QSysInfo>

#include <QDebug>

QString OSRetriever::retrieve()
{
    QString kernelType = QSysInfo::kernelType();
    QString productVersion = QSysInfo::productVersion();

    qDebug() << "kernelType: " << kernelType;
    qDebug() << "Product Version: " << productVersion;

    if (kernelType.compare("linux")) {
        qDebug() << "LINUX ERKANNT!";
        return "linux";
    }

    if (productVersion.contains("windows")) {
        qDebug() << "WINDOWS ERKANNT!";
        return "windows";
    }

    if (productVersion.contains("macOS")) {
        qDebug() << "MAC OS ERKANNT!";
        return "mac-os";
    }

    return "";
}
