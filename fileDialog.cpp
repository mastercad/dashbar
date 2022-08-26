#include "fileDialog.h"
#include "mainwindow.h"

#include <QDir>
#include <QIcon>
#include <QLabel>
#include <QWizard>
#include <QStringList>
#include <QPushButton>
#include <QFileDialog>
#include <QGridLayout>
#include <QStringList>
#include <QMessageBox>

#ifdef Q_WS_WIN
#include <qt_windows.h>
#endif

#include <QDebug>

FileDialog::FileDialog(Application* application, Applications* applications, QWidget* parent) : application(application), applications(applications), parent(parent) {
    setWindowTitle(tr("Select File"));

#ifdef Q_WS_WIN
    qDebug() << "Q_WS_WIN active!";
#endif
//    QIcon::fromTheme();

    QGridLayout *mainLayout = new QGridLayout(this);

    nameEdit = new QLineEdit();
    nameEdit->setText(application->getName());
    nameEdit->setPlaceholderText(tr("Name"));

    fileEdit = new QLineEdit();
    fileEdit->setText(application->getPath());
    fileEdit->setPlaceholderText(tr("Executable*"));

    iconEdit = new QLineEdit();

    iconButton = new QPushButton();
    iconButton->setFixedSize(QSize(64, 64));
    iconButton->setIcon(QPixmap(":/icons/default_icon.png"));
    iconButton->setIconSize(QSize(64, 64));
    connect(iconButton, SIGNAL(clicked()), this, SLOT(onSelectIconClicked()));

    if (!application->getIcon().startsWith(":")
        && !application->getIcon().isEmpty()
    ) {
        iconEdit->setText(application->getIcon());
        iconButton->setIcon(QPixmap(application->getIcon()));
    }

    commandEdit = new QLineEdit();
    commandEdit->setText(application->getCommand());
    commandEdit->setPlaceholderText(tr("Command"));

    paramsEdit = new QLineEdit();
    paramsEdit->setText(application->getParameters());
    paramsEdit->setPlaceholderText(tr("Parameters"));

    absolutePathCheckbox = new QCheckBox();
    absolutePathCheckbox->setCheckState(Qt::CheckState::Checked);

    QPushButton* fileButton = new QPushButton(tr("&Browse..."));
    connect(fileButton, SIGNAL(clicked()), this, SLOT(onSelectFileClicked()));

    QPushButton* cancelButton = new QPushButton(tr("&Cancel"));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(onCancelClicked()));

    QPushButton* saveButton = new QPushButton(tr("&Save"));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(onSaveClicked()));

    mainLayout->addWidget(iconButton, 0, 0, 3, 1);

    mainLayout->addWidget(nameEdit, 1, 1, 1, 2);

    mainLayout->addWidget(fileEdit, 2, 1);
    mainLayout->addWidget(fileButton, 2, 2);

    mainLayout->addWidget(new QLabel(tr("Absolut Path:")), 3, 0);
    mainLayout->addWidget(absolutePathCheckbox, 3, 1);

    mainLayout->addWidget(new QLabel(tr("Command:")), 4, 0);
    mainLayout->addWidget(commandEdit, 4, 1, 1, 2);

    mainLayout->addWidget(new QLabel(tr("Parameters:")), 5, 0);
    mainLayout->addWidget(paramsEdit, 5, 1, 1, 2);

    mainLayout->addWidget(cancelButton, 7, 1);
    mainLayout->addWidget(saveButton, 7, 2);
}

void FileDialog::onSelectFileClicked() {
    QFileDialog* fileDialog = new QFileDialog(this, tr("Select executable file"), application->getPath());
    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog->setFileMode(QFileDialog::ExistingFile);
//    fileDialog->setOption(QFileDialog::DontUseNativeDialog, true);
    fileDialog->setFilter(QDir::Executable | QDir::Files);

    if (QDialog::Accepted != fileDialog->exec()) {
        return;
    }

    QStringList filePathNames = fileDialog->selectedFiles();
    QString filePathName = filePathNames[0];
    fileEdit->setText(filePathName);
}

void FileDialog::onSelectIconClicked() {
    QString selfilter = tr("Images (*.jpg *.jpeg *.png *.ico *.svg)");
    QString filePathName = QFileDialog::getOpenFileName(
        this,
        tr("Select executable file"),
        application->getIcon(),
        tr(QString("All files (*.*);;").append(selfilter).toStdString().c_str()),
        &selfilter
    );
    iconEdit->setText(filePathName);

    if (filePathName.isEmpty()) {
        iconButton->setIcon(QPixmap(":/icons/default_icon.png"));
    } else {
        iconButton->setIcon(QPixmap(filePathName));
    }
    iconButton->setIconSize(QSize(64, 64));
}

void FileDialog::onCancelClicked() {
    this->close();
}

void FileDialog::onSaveClicked() {
    QString currentPath = application->getPath();
    QString executablePath = fileEdit->text().trimmed();
    QString iconPath = "";

    QFile executableFile(executablePath);
    QFileInfo executableFileInfo(executableFile);

    if (!iconEdit->text().trimmed().startsWith(':')) {
        iconPath = iconEdit->text().trimmed();
    }
    QFile iconFile(iconPath);
    QFileInfo iconFileInfo(iconFile);

    if (!executableFileInfo.exists()
        || !executableFileInfo.isReadable()
    ) {
        QMessageBox::critical(this, tr("Problem loading file"), QString("File \"").append(executablePath).append("\" is not readable!"));
        return;
    }

    if (!iconPath.trimmed().isEmpty()
        && (
            !iconFileInfo.exists()
            || !iconFileInfo.isReadable()
        )
    ) {
        QMessageBox::critical(this, tr("Problem loading file"), QString("File \"").append(iconPath).append("\" is not readable!"));
        return;
    }

    if (Qt::CheckState::Unchecked == absolutePathCheckbox->checkState()) {
        executablePath = convertToRelativePath(executablePath);
    }

    application->setCommand(commandEdit->text().trimmed());
    application->setName(nameEdit->text().trimmed());
    application->setPath(executablePath);
    application->setIcon(iconPath);
    application->setParameters(paramsEdit->text().trimmed());

    if (currentPath != executablePath) {
        applications->remove(currentPath);
    }
    applications->add(application);

    dynamic_cast<MainWindow*>(parent)->rewriteSettings();
    dynamic_cast<MainWindow*>(parent)->createButtons();

    this->close();
}

QString FileDialog::convertToRelativePath(QString& path) {
    QFile filePath(path);
    QDir dirPath(QDir::currentPath());

    return dirPath.relativeFilePath(filePath.fileName());
}
