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
    QMapIterator<QString, ApplicationRules*> applicationRule(*keys);
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

    QMapIterator<QString, Application*> iterator(*applications->getData());

    while (iterator.hasNext()) {
        iterator.next();
        QString key = QString(retrieveApplicationName(iterator.value()));
        if (!iterator.value()->get("name").isEmpty()
            && !iterator.value()->get("name").startsWith(":")
            ) {
            settings->setValue(key+"/name", iterator.value()->get("name"));
        }

        if (!iterator.value()->get("icon").isEmpty()
            && !iterator.value()->get("icon").startsWith(":")
            ) {
            settings->setValue(key+"/icon", iterator.value()->get("icon"));
        }

        if (!iterator.value()->get("linux-path").isEmpty()) {
            settings->setValue(key+"/linux-path", iterator.value()->get("linux-path"));
        }
        if (!iterator.value()->get("windows-path").isEmpty()) {
            settings->setValue(key+"/windows-path", iterator.value()->get("windows-path"));
        }
        if (!iterator.value()->get("mac-os-path").isEmpty()) {
            settings->setValue(key+"/mac-os-path", iterator.value()->get("mac-os-path"));
        }

        if (!iterator.value()->get("linux-command").isEmpty()) {
            settings->setValue(key+"/linux-command", iterator.value()->get("linux-command"));
        }
        if (!iterator.value()->get("windows-command").isEmpty()) {
            settings->setValue(key+"/windows-command", iterator.value()->get("windows-command"));
        }
        if (!iterator.value()->get("mac-os-command").isEmpty()) {
            settings->setValue(key+"/mac-os-command", iterator.value()->get("mac-os-command"));
        }

        if (!iterator.value()->get("linux-params").isEmpty()) {
            settings->setValue(key+"/linux-params", iterator.value()->get("linux-params"));
        }
        if (!iterator.value()->get("windows-params").isEmpty()) {
            settings->setValue(key+"/windows-params", iterator.value()->get("windows-params"));
        }
        if (!iterator.value()->get("mac-os-params").isEmpty()) {
            settings->setValue(key+"/mac-os-params", iterator.value()->get("mac-os-params"));
        }

    }

    settings->endGroup();
    return settings;
}

QString Mapper::retrieveApplicationName(const Application* application) {
    if (!application->getName().trimmed().isEmpty()) {
        return application->getName();
    }

    QString fileName;
    if (!application->getLinuxPath().isEmpty()) {
        fileName = application->getLinuxPath();
    } else if (!application->getWindowsPath().isEmpty()) {
        fileName = application->getWindowsPath();
    } else if (!application->getMacOSPath().isEmpty()) {
        fileName = application->getMacOSPath();
    }

    if (fileName.isEmpty()) {
        return "";
    }

    QFile file(fileName);
    QFileInfo fileInfo(file.fileName());

    return fileInfo.baseName().trimmed();
}
