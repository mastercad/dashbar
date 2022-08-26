#ifndef __BUTTON_MANAGER_H__
#define __BUTTON_MANAGER_H__

#include "applications.h"

#include <QObject>
#include <QHash>
#include <QString>
#include <QProcess>
#include <QPushButton>
#include <QSignalMapper>

class ButtonManager: public QWidget
{
    Q_OBJECT
    
    public:
        ButtonManager(Applications* applications, QWidget* parent = nullptr);
        ~ButtonManager();
        QPushButton* generate(Application* application);
    
    public slots:
        void startApplication(QString applicationIdentifier);
        void processIsFinished(int exitCode, QProcess::ExitStatus exitStatus);
        
    private:
        QWidget* parent;
        Applications* applications;
        QSignalMapper* signalMapper;
        QHash<QString, QPushButton*>* buttons;
        QHash<QString, QProcess*>* processes;
};

#endif
