#ifndef __MAPPER_H__
#define __MAPPER_H__

#include "config.h"
#include "applications.h"

#include <QSettings>
#include <QStringList>

class Mapper
{
    public:
        Config* map(QSettings* settings, Config* config);
        Applications* map(QSettings* settings, Applications* applications);
        Application* map(QSettings* applicationSettings, Application* application);
        QSettings* map(Config* config, QSettings* settings);
        QSettings* map(Applications* applications, QSettings* settings);
        QString retrieveApplicationName(const Application* application);

    private:
        QString generateMapKey(const QString identifier, const QString key);
};

#endif
