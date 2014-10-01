#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "note.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    createAction();
    systemTray = new QSystemTrayIcon();
    systemTray->setToolTip(QString("便签"));
    systemTray->setIcon(QIcon(":/image/image/icon.png"));
    systemTray->setContextMenu(rightKeyMenu);
    connect(systemTray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(iconIsActived(QSystemTrayIcon::ActivationReason)));
    systemTray->show();
    systemTray->showMessage(QString("便签"),QString("可点击这里退出"));
    ui->setupUi(this);
    ui->listWidget->setViewMode(QListView::IconMode);
    this->hide();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showFirstNote()
{
    systemTray->show();
    note *firstNote = new note();
    firstNote->show();

}
void MainWindow::createNewNote()
{

}

void MainWindow::on_actionNew_triggered()
{
    note *shownote = new note();
    shownote->show();
}
void MainWindow::createAction()
{
    rightKeyMenu = new QMenu();
    newNoteAction = new QAction(tr("&添加便签"), this);
    closeNoteAction = new QAction(tr("关闭便签"),this);
    showManageWidgetAction = new QAction(tr("便签管理器"),this);
    closeAppAction = new QAction(tr("&退出程序"),this);
    rightKeyMenu->addAction(newNoteAction);
    rightKeyMenu->addAction(closeNoteAction);
    rightKeyMenu->addAction(showManageWidgetAction);
    rightKeyMenu->addAction(closeAppAction);
    connect(newNoteAction,SIGNAL(triggered()),this,SLOT(on_actionNew_triggered()));
    connect(showManageWidgetAction,SIGNAL(triggered()),this,SLOT(show()));
    connect(closeAppAction,SIGNAL(triggered()),this,SLOT(exitApp()));

}
void MainWindow::showManageWidget()
{
    this->show();
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    rightKeyMenu->clear();

    rightKeyMenu->exec(QCursor::pos());
    event->accept();
}

void MainWindow::iconIsActived(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
         //点击托盘显示窗口
         case QSystemTrayIcon::Trigger:
          {
            showMinimized();
            break;
          }
         //双击托盘显示窗口
         case QSystemTrayIcon::DoubleClick:
         {
           systemTray->show();
           break;
         }
         default:
          break;
         }

}
void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
}
void MainWindow::changeEvent(QCloseEvent *event)
{
    if((event->type() == QEvent::WindowStateChange) && this->isMinimized())
    {
        this->hide();
    }

}

void MainWindow::exitApp()
{
    exit(0);
}








