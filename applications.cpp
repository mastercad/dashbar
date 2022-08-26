#include "applications.h"

#include <QDebug>

Applications::Applications() {
    data = new QHash<QString, Application*>();    
}

Applications* Applications::add(Application* application) {
    data->insert(application->getPath(), application);
    
    return this;
}

Application* Applications::get(const QString identifier) {
    return data->value(identifier);
}

void Applications::remove(const QString identifier) {
    data->remove(identifier);
}
