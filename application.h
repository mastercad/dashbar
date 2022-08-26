#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "applicationRules.h"

#include <QString>
#include <QHash>

class Application
{
    public:
        Application();
        
        QString getPath() const;
        Application* setPath(const QString path);
        
        QString getName() const;
        Application* setName(const QString name);
        
        QString getIcon() const;
        Application* setIcon(const QString icon);
        
        QString getCommand() const;
        Application* setCommand(const QString command);
        
        QString getParameters() const;
        Application* setParameters(const QString parameters);
        
        QString get(QString key) const;
        Application* set(const QString key, const QString value);
        
        QHash<QString, ApplicationRules*>* getKeys();
        
    private:
        QHash<QString, ApplicationRules*>* keys;
        QHash<QString, QString>* data;
};

#endif
