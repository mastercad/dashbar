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
    
    public Q_SLOTS:
        void startApplication(QString applicationIdentifier);
        void processIsFinished(int exitCode, QProcess::ExitStatus exitStatus);
        void errorOccurred(QProcess::ProcessError error);
        
    private:
        QWidget* parent;
        Applications* applications;
        QHash<QString, QProcess*>* processes;

    // this member are only protected to make inheritance for testing possible
    protected:
        QSignalMapper* signalMapper;
        QHash<QString, QPushButton*>* buttons;

};

#endif
