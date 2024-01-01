#ifndef __APPLICATIONS_H__
#define __APPLICATIONS_H__

#include "application.h"

#include <QString>
#include <QMap>

#include <QMetaType>

class Applications
{
    public:
        Applications();
        QString getIdentifier() {
            return "applications";
        }
        Applications* add(Application* application);
        Application* get(const QString applicationName);
        QMap<QString, Application*>* getData() const {return data;}
        void remove(const QString identifier);
    
    private:
        QMap<QString, Application*>* data;
};

Q_DECLARE_METATYPE(Applications*);

#endif
