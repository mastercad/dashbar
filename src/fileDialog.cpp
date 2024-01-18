#include "fileDialog.h"
#include "mainwindow.h"
#include "osretriever.h"

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
#include <QSysInfo>

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

    currentOS = OSRetriever::retrieve();

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

    nameEdit = new QLineEdit();
    nameEdit->setText(application->getName());
    nameEdit->setPlaceholderText(tr("Name"));

    QGridLayout *mainLayout = new QGridLayout(this);

    mainLayout->addWidget(iconButton, 0, 0);
    mainLayout->addWidget(nameEdit, 0, 1);

    fileTabWidget = this->createFileTabWidget();

    if ("linux" == currentOS) {
        fileTabWidget->setCurrentIndex(0);
    } else if ("windows" == currentOS) {
        fileTabWidget->setCurrentIndex(1);
    } else if ("mac-os" == currentOS) {
        fileTabWidget->setCurrentIndex(2);
    }

    mainLayout->addWidget(fileTabWidget, 2, 0, 1, 2);
}

QTabWidget* FileDialog::createFileTabWidget()
{
    QTabWidget *tabWidget = new QTabWidget(this);
    tabWidget->addTab(this->createLinuxFileDialogTab(), "Linux");
    tabWidget->addTab(this->createWindowsFileDialogTab(), "Windows");
    tabWidget->addTab(this->createMacOSFileDialogTab(), "MacOS");

    return tabWidget;
}

QWidget* FileDialog::createLinuxFileDialogTab()
{
    QWidget *widget = new QWidget(this);
    QGridLayout *layout = new QGridLayout(this);

    fileLinuxEdit = new QLineEdit();
    fileLinuxEdit->setText(application->getLinuxPath());
    fileLinuxEdit->setPlaceholderText(tr("Executable*"));

    commandLinuxEdit = new QLineEdit();
    commandLinuxEdit->setText(application->getLinuxCommand());
    commandLinuxEdit->setPlaceholderText(tr("Command"));

    paramsLinuxEdit = new QLineEdit();
    paramsLinuxEdit->setText(application->getLinuxParameters());
    paramsLinuxEdit->setPlaceholderText(tr("Parameters"));

    absolutePathLinuxCheckbox = new QCheckBox();

    if (!application->getLinuxPath().isEmpty()
        && application->getLinuxPath().startsWith("/")
    ) {
        absolutePathLinuxCheckbox->setCheckState(Qt::CheckState::Checked);
    }

    QPushButton* fileButton = new QPushButton(tr("&Browse..."));
    connect(fileButton, SIGNAL(clicked()), this, SLOT(onSelectFileClicked()));
    fileButton->setProperty("currentOS", "linux");

    QPushButton* cancelButton = new QPushButton(tr("&Cancel"));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
    cancelButton->setProperty("currentOS", "linux");

    QPushButton* saveButton = new QPushButton(tr("&Save"));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(onSaveClicked()));
    saveButton->setProperty("currentOS", "linux");

    layout->addWidget(new QLabel(tr("File:")), 0, 0);
    layout->addWidget(fileLinuxEdit, 0, 1);
    layout->addWidget(fileButton, 0, 2);

    layout->addWidget(new QLabel(tr("Absolut Path:")), 1, 0);
    layout->addWidget(absolutePathLinuxCheckbox, 1, 1);

    layout->addWidget(new QLabel(tr("Command:")), 2, 0);
    layout->addWidget(commandLinuxEdit, 2, 1, 1, 2);

    layout->addWidget(new QLabel(tr("Parameters:")), 3, 0);
    layout->addWidget(paramsLinuxEdit, 3, 1, 1, 2);

    layout->addWidget(cancelButton, 4, 1);
    layout->addWidget(saveButton, 4, 2);

    widget->setLayout(layout);

    return widget;
}

QWidget* FileDialog::createWindowsFileDialogTab()
{
    QWidget *widget = new QWidget(this);
    QGridLayout *layout = new QGridLayout(this);

    fileWindowsEdit = new QLineEdit();
    fileWindowsEdit->setText(application->getWindowsPath());
    fileWindowsEdit->setPlaceholderText(tr("Executable*"));

    commandWindowsEdit = new QLineEdit();
    commandWindowsEdit->setText(application->getWindowsCommand());
    commandWindowsEdit->setPlaceholderText(tr("Command"));

    paramsWindowsEdit = new QLineEdit();
    paramsWindowsEdit->setText(application->getWindowsParameters());
    paramsWindowsEdit->setPlaceholderText(tr("Parameters"));

    absolutePathWindowsCheckbox = new QCheckBox();

    if (!application->getWindowsPath().isEmpty()
        && application->getWindowsPath().startsWith("/")
    ) {
        absolutePathWindowsCheckbox->setCheckState(Qt::CheckState::Checked);
    }

    QPushButton* fileButton = new QPushButton(tr("&Browse..."));
    connect(fileButton, SIGNAL(clicked()), this, SLOT(onSelectFileClicked()));
    fileButton->setProperty("currentOS", "linux");

    QPushButton* cancelButton = new QPushButton(tr("&Cancel"));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
    cancelButton->setProperty("currentOS", "linux");

    QPushButton* saveButton = new QPushButton(tr("&Save"));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(onSaveClicked()));
    saveButton->setProperty("currentOS", "windows");

    layout->addWidget(new QLabel(tr("File:")), 0, 0);
    layout->addWidget(fileWindowsEdit, 0, 1);
    layout->addWidget(fileButton, 0, 2);

    layout->addWidget(new QLabel(tr("Absolut Path:")), 1, 0);
    layout->addWidget(absolutePathWindowsCheckbox, 1, 1);

    layout->addWidget(new QLabel(tr("Command:")), 2, 0);
    layout->addWidget(commandWindowsEdit, 2, 1, 1, 2);

    layout->addWidget(new QLabel(tr("Parameters:")), 3, 0);
    layout->addWidget(paramsWindowsEdit, 3, 1, 1, 2);

    layout->addWidget(cancelButton, 4, 1);
    layout->addWidget(saveButton, 4, 2);

    widget->setLayout(layout);

    return widget;
}

QWidget* FileDialog::createMacOSFileDialogTab()
{
    QWidget *widget = new QWidget(this);
    QGridLayout *layout = new QGridLayout(this);

    fileMacOSEdit = new QLineEdit();
    fileMacOSEdit->setText(application->getMacOSPath());
    fileMacOSEdit->setPlaceholderText(tr("Executable*"));

    commandMacOSEdit = new QLineEdit();
    commandMacOSEdit->setText(application->getMacOSCommand());
    commandMacOSEdit->setPlaceholderText(tr("Command"));

    paramsMacOSEdit = new QLineEdit();
    paramsMacOSEdit->setText(application->getMacOSParameters());
    paramsMacOSEdit->setPlaceholderText(tr("Parameters"));

    absolutePathMacOSCheckbox = new QCheckBox();

    if (!application->getMacOSPath().isEmpty()
        && application->getMacOSPath().startsWith("/")
    ) {
        absolutePathMacOSCheckbox->setCheckState(Qt::CheckState::Checked);
    }

    QPushButton* fileButton = new QPushButton(tr("&Browse..."));
    connect(fileButton, SIGNAL(clicked()), this, SLOT(onSelectFileClicked()));
    fileButton->setProperty("currentOS", "mac-os");

    QPushButton* cancelButton = new QPushButton(tr("&Cancel"));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
    cancelButton->setProperty("currentOS", "mac-os");

    QPushButton* saveButton = new QPushButton(tr("&Save"));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(onSaveClicked()));
    saveButton->setProperty("currentOS", "mac-os");

    layout->addWidget(new QLabel(tr("File:")), 0, 0);
    layout->addWidget(fileMacOSEdit, 0, 1);
    layout->addWidget(fileButton, 0, 2);

    layout->addWidget(new QLabel(tr("Absolut Path:")), 1, 0);
    layout->addWidget(absolutePathMacOSCheckbox, 1, 1);

    layout->addWidget(new QLabel(tr("Command:")), 2, 0);
    layout->addWidget(commandMacOSEdit, 2, 1, 1, 2);

    layout->addWidget(new QLabel(tr("Parameters:")), 3, 0);
    layout->addWidget(paramsMacOSEdit, 3, 1, 1, 2);

    layout->addWidget(cancelButton, 4, 1);
    layout->addWidget(saveButton, 4, 2);

    widget->setLayout(layout);

    return widget;
}

void FileDialog::onSelectFileClicked() {
    QString kernelType = sender()->property("currentOS").toString();

    QFileDialog* fileDialog = new QFileDialog(this, tr("Select executable file"), application->retrievePath(kernelType));
    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setFilter(QDir::Executable | QDir::Files);

    if (QDialog::Accepted != fileDialog->exec()) {
        return;
    }

    QStringList filePathNames = fileDialog->selectedFiles();
    QString filePathName = filePathNames[0];


    int currentTabIndex = fileTabWidget->currentIndex();

    qDebug() << "CurrentTab Index: " << currentTabIndex;

    if (0 == currentTabIndex) {
        fileLinuxEdit->setText(filePathName);
    } else if (1 == currentTabIndex) {
        fileWindowsEdit->setText(filePathName);
    } else if (2 == currentTabIndex) {
        fileMacOSEdit->setText(filePathName);
    }
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

    QString kernelType = sender()->property("currentOS").toString();
    QString iconPath = "";

    application->setName(nameEdit->text().trimmed());

    QFile iconFile(iconPath);
    QFileInfo iconFileInfo(iconFile);

    if (!iconPath.trimmed().isEmpty()
        && (
            !iconFileInfo.exists()
            || !iconFileInfo.isReadable()
            )
    ) {
        QMessageBox::critical(this, tr("Problem loading file"), QString("File \"").append(iconPath).append("\" is not readable!"));
        return;
    }

    application->setIcon(iconPath);

    QString currentPath = application->retrievePath(kernelType);

    QString executableLinuxPath = fileLinuxEdit->text().trimmed();
    QString executableWindowsPath = fileWindowsEdit->text().trimmed();
    QString executableMacOSPath = fileMacOSEdit->text().trimmed();

    if (executableMacOSPath.isEmpty()
        && executableLinuxPath.isEmpty()
        && executableWindowsPath.isEmpty()
    ) {
        applications->remove(application->getName());
        QMessageBox::critical(this, tr("No executable path provided."), QString("The file path for at least one operating system must be stored."));
        return;
    }

    qDebug() << "LINUX PATH: *" << executableLinuxPath << "*";
    qDebug() << "WINDOWS PATH: *" << executableWindowsPath << "*";
    qDebug() << "MAC OS PATH: *" << executableMacOSPath << "*";

    if (!executableLinuxPath.isEmpty()) {
        QFile executableLinuxFile(executableLinuxPath);
        QFileInfo executableLinuxFileInfo(executableLinuxFile);

        if (!iconEdit->text().trimmed().startsWith(':')) {
            iconPath = iconEdit->text().trimmed();
        }

        if (!executableLinuxFileInfo.exists()
            || !executableLinuxFileInfo.isReadable()
            ) {
            QMessageBox::critical(this, tr("Problem loading linux file"), QString("File \"").append(executableLinuxPath).append("\" is not readable!"));
            return;
        }
    }

    if (!executableLinuxPath.isEmpty()) {
        QFile executableLinuxFile(executableLinuxPath);
        QFileInfo executableLinuxFileInfo(executableLinuxFile);

        if (!iconEdit->text().trimmed().startsWith(':')) {
            iconPath = iconEdit->text().trimmed();
        }

        if (!executableLinuxFileInfo.exists()
            || !executableLinuxFileInfo.isReadable()
            ) {
            QMessageBox::critical(this, tr("Problem loading linux file"), QString("File \"").append(executableLinuxPath).append("\" is not readable!"));
            return;
        }
    }

    if (!executableWindowsPath.isEmpty()) {
        QFile executableWindowsFile(executableWindowsPath);
        QFileInfo executableWindowsFileInfo(executableWindowsFile);

        if (!iconEdit->text().trimmed().startsWith(':')) {
            iconPath = iconEdit->text().trimmed();
        }

        if (!executableWindowsFileInfo.exists()
            || !executableWindowsFileInfo.isReadable()
            ) {
            QMessageBox::critical(this, tr("Problem loading windows file"), QString("File \"").append(executableWindowsPath).append("\" is not readable!"));
            return;
        }
    }

    if (!executableMacOSPath.isEmpty()) {
        QFile executableMacOSFile(executableMacOSPath);
        QFileInfo executableMacOSFileInfo(executableMacOSFile);

        if (!iconEdit->text().trimmed().startsWith(':')) {
            iconPath = iconEdit->text().trimmed();
        }

        if (!executableMacOSFileInfo.exists()
            || !executableMacOSFileInfo.isReadable()
            ) {
            QMessageBox::critical(this, tr("Problem loading macOS file"), QString("File \"").append(executableMacOSPath).append("\" is not readable!"));
            return;
        }
    }

    if (Qt::CheckState::Unchecked == absolutePathLinuxCheckbox->checkState()) {
        executableLinuxPath = convertToRelativePath(executableLinuxPath);
    }

    if (Qt::CheckState::Unchecked == absolutePathWindowsCheckbox->checkState()) {
        executableWindowsPath = convertToRelativePath(executableWindowsPath);
    }

    if (Qt::CheckState::Unchecked == absolutePathMacOSCheckbox->checkState()) {
        executableMacOSPath = convertToRelativePath(executableMacOSPath);
    }

    application->setLinuxCommand(commandLinuxEdit->text().trimmed());
    application->setLinuxPath(executableLinuxPath);
    application->setLinuxParameters(paramsLinuxEdit->text().trimmed());

    application->setWindowsCommand(commandWindowsEdit->text().trimmed());
    application->setWindowsPath(executableWindowsPath);
    application->setWindowsParameters(paramsWindowsEdit->text().trimmed());

    application->setMacOSCommand(commandMacOSEdit->text().trimmed());
    application->setMacOSPath(executableMacOSPath);
    application->setMacOSParameters(paramsMacOSEdit->text().trimmed());

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
