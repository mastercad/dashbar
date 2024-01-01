#ifndef __FILEDIALOG_H__
#define __FILEDIALOG_H__

#include "application.h"
#include "applications.h"

#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QFileDialog>
#include <QCheckBox>
#include <QTabWidget>
#include <QWidget>

class FileDialog: public QDialog
{
    Q_OBJECT
    
    public:
        FileDialog(Application* application, Applications* applications, QWidget* parent);
        QString convertToRelativePath(QString& path);

    private:
        QTabWidget* createFileTabWidget();
        QWidget* createLinuxFileDialogTab();
        QWidget* createWindowsFileDialogTab();
        QWidget* createMacOSFileDialogTab();

    public Q_SLOTS:
        void onSelectFileClicked();
        void onSelectIconClicked();
        void onCancelClicked();
        void onSaveClicked();

    private:
        QLineEdit* iconEdit;
        QLineEdit* nameEdit;
        QPushButton* iconButton;

        QTabWidget *fileTabWidget;

        QLineEdit* fileLinuxEdit;
        QLineEdit* fileWindowsEdit;
        QLineEdit* fileMacOSEdit;
        QLineEdit* commandLinuxEdit;
        QLineEdit* commandWindowsEdit;
        QLineEdit* commandMacOSEdit;
        QLineEdit* paramsLinuxEdit;
        QLineEdit* paramsWindowsEdit;
        QLineEdit* paramsMacOSEdit;
        QCheckBox* absolutePathLinuxCheckbox;
        QCheckBox* absolutePathWindowsCheckbox;
        QCheckBox* absolutePathMacOSCheckbox;

        QString currentOS;

        Application* application;
        Applications* applications;
        QWidget* parent;
};

#endif
