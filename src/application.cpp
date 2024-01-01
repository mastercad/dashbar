#include "application.h"

#include <QDebug>

Application::Application() {
    keys = new QMap<QString, ApplicationRules*>();
    data = new QMap<QString, QString>();

    keys->insert("name", new ApplicationRules(false, "", false));
    keys->insert("icon", new ApplicationRules(false, ":/icons/default_icon.png"));

    keys->insert("linux-path", new ApplicationRules(true, ""));
    keys->insert("linux-command", new ApplicationRules());
    keys->insert("linux-params", new ApplicationRules());

    keys->insert("windows-path", new ApplicationRules(true, ""));
    keys->insert("windows-command", new ApplicationRules());
    keys->insert("windows-params", new ApplicationRules());

    keys->insert("mac-os-path", new ApplicationRules(true, ""));
    keys->insert("mac-os-command", new ApplicationRules());
    keys->insert("mac-os-params", new ApplicationRules());
}

QString Application::get(QString key) const {
    return this->data->value(key);
}

Application * Application::set(const QString key, const QString value) {
    this->data->insert(key, value);
    
    return this;
}

QMap<QString, ApplicationRules*>* Application::getKeys() {
    return keys;
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

QString Application::getLinuxPath() const {
    return this->get("linux-path");
}

Application* Application::setLinuxPath(const QString path) {
    this->set("linux-path", path);

    return this;
}

QString Application::getWindowsPath() const {
    return this->get("windows-path");
}

Application* Application::setWindowsPath(const QString path) {
    this->set("windows-path", path);

    return this;
}

QString Application::getMacOSPath() const {
    return this->get("mac-os-path");
}

Application* Application::setMacOSPath(const QString path) {
    this->set("mac-os-path", path);

    return this;
}

QString Application::retrievePath(const QString kernelType) const
{
    return this->get(kernelType + "-path");
}

QString Application::getLinuxCommand() const {
    return this->get("linux-command");
}

Application* Application::setLinuxCommand(const QString command) {
    this->set("linux-command", command);

    return this;
}

QString Application::getWindowsCommand() const {
    return this->get("windows-command");
}

Application* Application::setWindowsCommand(const QString command) {
    this->set("windows-command", command);

    return this;
}

QString Application::getMacOSCommand() const {
    return this->get("mac-os-command");
}

Application* Application::setMacOSCommand(const QString command) {
    this->set("mac-os-command", command);

    return this;
}

QString Application::retrieveCommand(const QString kernelType) const
{
    return this->get(kernelType + "-command");
}

QString Application::getLinuxParameters() const {
    return this->get("linux-params");
}

Application* Application::setLinuxParameters(const QString parameters) {
    this->set("linux-params", parameters);

    return this;
}

QString Application::getWindowsParameters() const {
    return this->get("windows-params");
}

Application* Application::setWindowsParameters(const QString parameters) {
    this->set("windows-params", parameters);

    return this;
}

QString Application::getMacOSParameters() const {
    return this->get("mac-os-params");
}

Application* Application::setMacOSParameters(const QString parameters) {
    this->set("mac-os-params", parameters);

    return this;
}

QString Application::retrieveParameters(const QString kernelType) const
{
    return this->get(kernelType + "-parameters");
}




