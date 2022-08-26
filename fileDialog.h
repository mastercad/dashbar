#ifndef __FILEDIALOG_H__
#define __FILEDIALOG_H__

#include "application.h"
#include "applications.h"

#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QFileDialog>
#include <QCheckBox>

class FileDialog: public QDialog
{
    Q_OBJECT
    
    public:
        FileDialog(Application* application, Applications* applications, QWidget* parent);
        QString convertToRelativePath(QString& path);

    public slots:
        void onSelectFileClicked();
        void onSelectIconClicked();
        void onCancelClicked();
        void onSaveClicked();

    private:
        QLineEdit* nameEdit;
        QLineEdit* fileEdit;
        QLineEdit* iconEdit;
        QLineEdit* commandEdit;
        QLineEdit* paramsEdit;
        QCheckBox* absolutePathCheckbox;
        QPushButton* iconButton;

        Application* application;
        Applications* applications;
        QWidget* parent;
};

#endif
