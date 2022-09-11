#include "buttonManager.h"
#include "application.h"

#include <QSignalMapper>
#include <QHashIterator>
#include <QMessageBox>
#include <QPixmap>
#include <QProcess>
#include <QIcon>
#include <QMenu>
#include <QRect>
#include <QSize>

#include <QDebug>

ButtonManager::ButtonManager(Applications* applications, QWidget* parent): parent(parent), applications(applications) {
    this->parent = parent;
    this->signalMapper = new QSignalMapper(parent);
    this->buttons = new QHash<QString, QPushButton*>;
    this->processes = new QHash<QString, QProcess*>;
    
    connect(signalMapper, &QSignalMapper::mappedString, this, &ButtonManager::startApplication);
}

QPushButton* ButtonManager::generate(Application* application) {
    QPushButton* button = new QPushButton("", parent);
    QPixmap buttonPixmap(application->getIcon());
    QIcon buttonIcon(buttonPixmap);

    button->setIcon(buttonIcon);
    button->setIconSize(QSize(64, 64));
    button->setToolTip(application->getName());
    button->setContextMenuPolicy(Qt::CustomContextMenu);
    button->setContextMenuPolicy(Qt::CustomContextMenu);

    // prevent add "+" button also in this collection because this button behaves completely different
    if (!application->getPath().isEmpty()) {
        connect(button, SIGNAL(clicked()), this->signalMapper, SLOT(map()));
        this->buttons->insert(application->getPath(), button);
        this->signalMapper->setMapping(button, application->getPath());
    }

    button->setMinimumSize(QSize(72, 72));
    button->setMaximumSize(QSize(72, 72));
    button->setFixedSize(QSize(72, 72));

    return button;
}

void ButtonManager::startApplication(QString applicationIdentifier) {
    Application* application = applications->get(applicationIdentifier);

    if (nullptr == application) {
        return qErrnoWarning("ButtonManager::startApplication: Application lost!");
    }

    QProcess* process = new QProcess(parent);

    QString command = application->getCommand();
    QString parameters = QString(application->getPath()).append(" ").append(application->getParameters());

    if (command.isEmpty()) {
        command = application->getPath();
        parameters = application->getParameters();
    }
    process->setProperty("applicationIdentifier", application->getPath());
    process->start(command.trimmed(), parameters.split(" "));

    connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processIsFinished(int,QProcess::ExitStatus)));
    connect(process, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(errorOccurred(QProcess::ProcessError)));

    QPushButton* button = buttons->value(application->getPath());

    button->setDisabled(true);

    processes->insert(application->getPath(), process);
}

void ButtonManager::errorOccurred(QProcess::ProcessError error) {
    QProcess* process = static_cast<QProcess*>(this->sender());
    QString errorOutput = process->readAllStandardError();

    if (!errorOutput.isEmpty()) {
        QMessageBox::critical(parent, tr("Error"), errorOutput);
    } else if (QProcess::FailedToStart == error){
        QMessageBox::critical(parent, tr("Failed to start"), tr("The process failed to start. Either the invoked program is missing, or you may have insufficient permissions or resources to invoke the program."));
    } else if (QProcess::Crashed == error) {
        QMessageBox::critical(parent, tr("Crashed"), tr("The process crashed some time after starting successfully."));
    } else if (QProcess::Timedout == error) {
        QMessageBox::critical(parent, tr("Timedout"), tr("Timeout reached."));
    } else if (QProcess::WriteError == error) {
        QMessageBox::critical(parent, tr("WriteError"), tr("An error occurred when attempting to write to the process. For example, the process may not be running, or it may have closed its input channel."));
    } else if (QProcess::ReadError == error) {
        QMessageBox::critical(parent, tr("ReadError"), tr("An error occurred when attempting to read from the process. For example, the process may not be running."));
    } else {
        QMessageBox::critical(parent, tr("Unknown error"), tr("An unknown error occurred."));
    }

    Application* application = applications->get(process->property("applicationIdentifier").toString());
    QPushButton* button = buttons->value(application->getPath());
    button->setDisabled(false);
}

void ButtonManager::processIsFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    QProcess* process = static_cast<QProcess*>(this->sender());

    qDebug() << "ExitCode: " << exitCode << " Exitstatus: " << exitStatus;

    Application* application = applications->get(process->property("applicationIdentifier").toString());
    QPushButton* button = buttons->value(application->getPath());
    button->setDisabled(false);
}

ButtonManager::~ButtonManager() {
    QHashIterator<QString, QProcess*> iterator(*processes);

    while(iterator.hasNext()) {
        iterator.next();
        QProcess* process = iterator.value();
        process->terminate();
        process->close();
    }
}
