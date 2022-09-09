#include "application.h"

#include <QDebug>

Application::Application() {
    keys = new QHash<QString, ApplicationRules*>();
    data = new QHash<QString, QString>();
    
    keys->insert("path", new ApplicationRules(true, ""));
    keys->insert("name", new ApplicationRules(false, "", false));
    keys->insert("icon", new ApplicationRules(false, ":/icons/default_icon.png"));
    keys->insert("cmd", new ApplicationRules());
    keys->insert("params", new ApplicationRules());
}

QString Application::get(QString key) const {
    return this->data->value(key);
}

Application * Application::set(const QString key, const QString value) {
    this->data->insert(key, value);
    
    return this;
}

QHash<QString, ApplicationRules*>* Application::getKeys() {
    return keys;
}

QString Application::getPath() const {
    return this->get("path");
}

Application* Application::setPath(const QString path) {
    this->set("path", path);
    
    return this;
}

QString Application::getName() const {
    return this->get("name");
}

Application* Application::setName(const QString name) {
    this->set("name", name);
    
    return this;
}

QString Application::getIcon() const {
    return this->get("icon");
}

Application* Application::setIcon(const QString icon) {
    this->set("icon", icon);
    
    return this;
}

QString Application::getCommand() const {
    return this->get("command");
}

Application* Application::setCommand(const QString command) {
    this->set("command", command);
    
    return this;
}

QString Application::getParameters() const {
    return this->get("params");
}

Application* Application::setParameters(const QString parameters) {
    this->set("params", parameters);
    
    return this;
}




