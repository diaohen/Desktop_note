#include "trayicon.h"

trayIcon::trayIcon():QWidget()
{
    QIcon icon = QIcon(":/image/image/icon.png");
    TrayIcon = new QSystemTrayIcon(this);
    TrayIcon->setIcon(icon);
    TrayIcon->setToolTip(tr("托盘"));
    QString title = tr("what happen ？");
    QString textc = tr("what's this ?");
    TrayIcon->show();
    TrayIcon->showMessage(title,textc,QSystemTrayIcon::Information,5000);
    connect(TrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(trayiconActivated(QSystemTrayIcon::ActivationReason)));
    miniSizeAction = new QAction(tr("最小化"),this);
    connect(miniSizeAction,SIGNAL(triggered()),this,SLOT(hide()));

}
