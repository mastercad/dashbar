#include "mainwindow.h"
#include "flowlayout.h"
#include "fileDialog.h"
#include "windowPositionManager.h"

#include <QHashIterator>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QString>
#include <QLabel>
#include <QMenu>
#include <QDir>

#include <QCloseEvent>
#include <QDialog>
#include <QAction>
#include <QCheckBox>
#include <QComboBox>
#include <QCoreApplication>
#include <QCloseEvent>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMessageBox>

#include <QScreen>

MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    config(new Config()),
    applications(new Applications()),
    windowPositionManager(new WindowPositionManager(this, applications))
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::FramelessWindowHint);

    createActions();
    createTrayIcon();

    trayIcon->show();

    flowLayout = new FlowLayout();
    flowLayout->setSizeConstraint(QLayout::SetNoConstraint);
    ui->centralwidget->setLayout(flowLayout);

    createButtons();
}

void MainWindow::show() {
    this->setVisible(false);
}

void MainWindow::createButtons() {
    clearLayout(flowLayout);

    buttonManager = new ButtonManager(applications, this);

    settings = new QSettings(QDir::currentPath()+"/settings.ini", QSettings::IniFormat);

    mapper.map(settings, config);
    mapper.map(settings, applications);

    QHashIterator<QString, Application*> iterator(*applications->getData());

    while (iterator.hasNext()) {
        iterator.next();
        QPushButton* button = buttonManager->generate(iterator.value());
        flowLayout->addWidget(button);

        button->setContextMenuPolicy(Qt::CustomContextMenu);
        QVariant variant;
        variant.setValue(iterator.value());
        button->setProperty("application", variant);

        connect(button, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    }

    Application* addButtonApplication = new Application();
    addButtonApplication->setIcon(":/icons/add_icon.png");

    QPushButton* addApplicationButton = buttonManager->generate(addButtonApplication);

    connect(addApplicationButton, SIGNAL(clicked()), this, SLOT(showFileSelect()));
    flowLayout->addWidget(addApplicationButton);

    ui->centralwidget->layout()->setSizeConstraint(QLayout::SetMinimumSize);

    windowPositionManager->resize(QApplication::primaryScreen()->geometry());
}

void MainWindow::rewriteSettings() {
    settings->clear();

    mapper.map(config, settings);
    mapper.map(applications, settings);
}

void MainWindow::clearLayout(QLayout *layout) {
    if (nullptr == layout) {
        return;
    }

    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}

void MainWindow::showContextMenu(const QPoint &pos) {
    QMenu contextMenu(tr("Dashbar Context menu"), this);

    Application* application = static_cast<Application*>(qobject_cast<QPushButton*>(this->sender())->property("application").value<Application*>());
    QVariant applicationVariant = QVariant::fromValue(application);

    QAction removeAction(tr("&Remove Data Point"), this);
    removeAction.setData(applicationVariant);
    connect(&removeAction, SIGNAL(triggered()), this, SLOT(removeApplication()));
    contextMenu.addAction(&removeAction);

    QAction editAction(tr("&Edit Data Point"), this);
    editAction.setData(applicationVariant);
    connect(&editAction, SIGNAL(triggered()), this, SLOT(showFileSelect()));
    contextMenu.addAction(&editAction);

    contextMenu.exec(qobject_cast<QPushButton*>(this->sender())->mapToGlobal(pos));
}

void MainWindow::removeApplication() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Remove"), tr("Do you realy want remove this entry?"), QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        Application* application = static_cast<Application*>(static_cast<QAction*>(this->sender())->data().value<Application*>());

        this->applications->remove(application->getPath());

        rewriteSettings();
        createButtons();
    }
}

void MainWindow::showFileSelect() {
    Application* application = static_cast<Application*>(static_cast<QAction*>(this->sender())->data().value<Application*>());

    if (nullptr == application) {
        application = new Application();

    }
    FileDialog fileDialog(application, applications, this);
    fileDialog.setModal(true);

    fileDialog.exec();
}

void MainWindow::setVisible(bool visible)
{
    minimizeAction->setEnabled(visible);
    restoreAction->setEnabled(!visible);
    QMainWindow::setVisible(visible);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!event->spontaneous()
        || !isVisible()
    ) {
        return;
    }

    if (trayIcon->isVisible()) {
        QMessageBox::information(
            this,
            tr("Systray"),
            tr("The program will keep running in the system tray. To terminate the program, choose <b>Quit</b> in the context menu of the system tray entry."));
        hide();
        event->ignore();
    }
}

void MainWindow::createActions() {
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void MainWindow::createTrayIcon() {
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QPixmap(":/icons/default_icon.png"));
    trayIcon->setContextMenu(trayIconMenu);
}

MainWindow::~MainWindow() {
    delete buttonManager;
    delete applications;
    delete config;
    delete settings;
    delete flowLayout;
    delete ui;
}
