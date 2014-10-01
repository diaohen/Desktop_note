#ifndef TRAYICON_H
#define TRAYICON_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include <QIcon>
#include <QString>

class trayIcon : public QWidget
{
    Q_OBJECT
public:
    explicit trayIcon();
private:
    QSystemTrayIcon *TrayIcon;
    QAction *newAction;
    QAction *miniSizeAction;
    QMenu *trayIconMenu;

signals:

public slots:
//    void trayiconActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif // TRAYICON_H
