#include "mapper.h"

#include <QHash>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QDebug>
#include <QSettings>
#include <QListIterator>

QString Mapper::generateMapKey(QString identifier, QString key) {
    return identifier.append("/").append(key);
}

// mapp settings in configs
Config* Mapper::map(QSettings* settings, Config* config) {
    auto keys = (config->getKeys());
    
    QHashIterator<QString, QString> iterator(*keys);
    
    while (iterator.hasNext()) {
        iterator.next();
        
        QString neededKey = generateMapKey(config->getIdentifier(), iterator.key());
        if (settings->contains(neededKey)) {
            config->add(iterator.key(), settings->value(neededKey).toString());
        } else {
            config->add(iterator.key(), iterator.value()); 
        }
    }
    
    return config;
}

// maps settings in applications
Applications* Mapper::map(QSettings* settings, Applications* applications) {
    settings->beginGroup("applications");
    
    QListIterator<QString> applicationEntries(settings->childGroups());

    while (applicationEntries.hasNext()) {
        QString applicationName = applicationEntries.next();

        settings->beginGroup(applicationName);

        Application* application = map(settings, applications->get(applicationName));

        if (application->getName().isEmpty()) {
            application->setName(applicationName);
        }

        applications->add(application);
        
        settings->endGroup();
    }
    
    settings->endGroup();
    
    return applications;
}

// maps setting in application
Application* Mapper::map(QSettings* applicationSettings, Application* application) {
    if (nullptr == application) {
        application = new Application();
    }

    auto keys = application->getKeys();
    QHashIterator<QString, ApplicationRules*> applicationRule(*keys);
    while (applicationRule.hasNext()) {
        applicationRule.next();
        if (true == applicationRule.value()->isIgnored()) {
            continue;
        }
        
        QString key = applicationRule.key();
        if (applicationSettings->contains(key)
            && !applicationSettings->value(key).toString().isEmpty()
        ) {
            application->set(key, applicationSettings->value(key).toString());
        } else {
            application->set(key, applicationRule.value()->getDefaultValue());
        }
    }

    return application;
}

// maps config in settings
QSettings* Mapper::map(Config* config, QSettings* settings) {
    settings->beginGroup("config");

    QHashIterator<QString, QString> iterator(*config->getKeys());

    while (iterator.hasNext()) {
        iterator.next();

        settings->setValue(iterator.key(), iterator.value());
    }

    settings->endGroup();
    return settings;
}

// maps applications in settings
QSettings* Mapper::map(Applications* applications, QSettings* settings) {
    settings->beginGroup("applications");

    QHashIterator<QString, Application*> iterator(*applications->getData());

    while (iterator.hasNext()) {
        iterator.next();
        QString key = QString(retrieveApplicationName(iterator.value()));

        settings->setValue(key+"/path", iterator.value()->get("path"));
        if (!iterator.value()->get("command").isEmpty()) {
            settings->setValue(key+"/command", iterator.value()->get("command"));
        }
        if (!iterator.value()->get("params").isEmpty()) {
            settings->setValue(key+"/params", iterator.value()->get("params"));
        }
        if (!iterator.value()->get("icon").isEmpty()
            && !iterator.value()->get("icon").startsWith(":")
        ) {
            settings->setValue(key+"/icon", iterator.value()->get("icon"));
        }
    }

    settings->endGroup();
    return settings;
}

QString Mapper::retrieveApplicationName(const Application* application) {
    if (!application->getName().trimmed().isEmpty()) {
        return application->getName();
    }

    QFile file(application->getPath());
    QFileInfo fileInfo(file.fileName());

    return fileInfo.baseName().trimmed();
}
