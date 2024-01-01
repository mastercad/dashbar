#include "applications.h"

#include <QDebug>

Applications::Applications() {
    data = new QMap<QString, Application*>();
}

Applications* Applications::add(Application* application) {
    data->insert(application->getName(), application);
    
    return this;
}

Application* Applications::get(const QString identifier) {
    return data->value(identifier);
}

void Applications::remove(const QString identifier) {
    data->remove(identifier);
}
