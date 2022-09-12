#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "flowlayout.h"
#include "mapper.h"
#include "config.h"
#include "applications.h"
#include "buttonManager.h"
#include "windowPositionManager.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QWidget>
#include <QString>
#include <QMap>
#include <QList>
#include <QMainWindow>

#include <QDialog>
#include <QSystemTrayIcon>
#include <QGroupBox>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QMenu>
#include <QRect>

QT_BEGIN_NAMESPACE
//namespace Ui { class MainWindow; }
class QAction;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QPushButton;
class QSpinBox;
class QTextEdit;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void createButtons();
    void rewriteSettings();
    void clearLayout(QLayout *layout);
    void resize(QRect screenGeometry);
    void setVisible(bool visible) override;
    void show();

protected:
    void closeEvent(QCloseEvent *event) override;

public Q_SLOTS:
    void showContextMenu(const QPoint &pos);
    void removeApplication();
    void showFileSelect();

private:
    void createIconGroupBox();
    void createMessageGroupBox();
    void createActions();
    void createTrayIcon();

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QWidget* parent;
    FlowLayout *flowLayout;
    Mapper mapper;
    Ui::MainWindow *ui;
    Config* config;
    Applications* applications;
    ButtonManager* buttonManager;
    QSettings* settings;
    WindowPositionManager* windowPositionManager;
};
#endif // MAINWINDOW_H
