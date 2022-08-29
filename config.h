#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <QHash>
#include <QString>

class Config
{
    public:
        Config();
        virtual QString getIdentifier() {
            return "config";
        }
        QHash<QString, QString>* getKeys();
        Config* add(const QString key, const QString value);
    
    private:
        QHash<QString, QString>* keys;
        QHash<QString, QString>* data;
};

#endif
