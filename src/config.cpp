#include "config.h"

#include <QDebug>

Config::Config() {
    keys = new QHash<QString, QString>();
    
    keys->insert("liveCheck", "true");
}

QHash<QString, QString>* Config::getKeys() {
    return keys;
}

Config* Config::add(const QString key, const QString value)
{
    keys->insert(key, value);
    
    return this;
}
