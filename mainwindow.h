#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <QSystemTrayIcon>
#include <QString>
#include <QCloseEvent>
#include <QEvent>
#include <QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void createAction();
    void contextMenuEvent(QContextMenuEvent *event);
    void closeEvent(QCloseEvent *event);
    void changeEvent(QCloseEvent *event);
    void showFirstNote();

    ~MainWindow();

private slots:
    void createNewNote();
    void iconIsActived(QSystemTrayIcon::ActivationReason reason);
    void exitApp();
    void showManageWidget();
    void on_actionNew_triggered();

private:
    Ui::MainWindow *ui;
    QMenu *rightKeyMenu;
    QAction *newNoteAction;
    QAction *closeNoteAction;
    QAction *showManageWidgetAction;
    QAction *closeAppAction;
    QSystemTrayIcon *systemTray;
};

#endif // MAINWINDOW_H
