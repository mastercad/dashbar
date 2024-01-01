#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "applicationRules.h"

#include <QString>
#include <QMap>

#include <QMetaType>

class Application
{
    public:
        Application();

        QString get(QString key) const;
        Application* set(const QString key, const QString value);

        QString getName() const;
        Application* setName(const QString name);

        QString getIcon() const;
        Application* setIcon(const QString icon);

        QString getLinuxPath() const;
        Application* setLinuxPath(const QString path);

        QString getWindowsPath() const;
        Application* setWindowsPath(const QString path);

        QString getMacOSPath() const;
        Application* setMacOSPath(const QString path);

        QString retrievePath(const QString kernelType) const;

        QString getLinuxCommand() const;
        Application* setLinuxCommand(const QString command);

        QString getWindowsCommand() const;
        Application* setWindowsCommand(const QString command);

        QString getMacOSCommand() const;
        Application* setMacOSCommand(const QString command);

        QString retrieveCommand(const QString kernelType) const;

        QString getLinuxParameters() const;
        Application* setLinuxParameters(const QString parameters);

        QString getWindowsParameters() const;
        Application* setWindowsParameters(const QString parameters);

        QString getMacOSParameters() const;
        Application* setMacOSParameters(const QString parameters);

        QString retrieveParameters(const QString kernelType) const;
        
        QMap<QString, ApplicationRules*>* getKeys();
        
    private:
        QMap<QString, ApplicationRules*>* keys;
        QMap<QString, QString>* data;
};

Q_DECLARE_METATYPE(Application*);

#endif
