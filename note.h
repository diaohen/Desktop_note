#ifndef NOTE_H
#define NOTE_H

#include <QDialog>
#include <QTextEdit>
#include <QContextMenuEvent>
#include <QMenu>
#include <QMouseEvent>
#include <QAction>
#include <QCursor>
#include <QPoint>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QMessageBox>
#include <QDateTime>
#define PADDING 2
namespace Ui {
class note;
}
enum Direction{//方向
    UP = 0,
    DOWN=1,
    LEFT,
    RIGHT,
    LEFTTOP,
    LEFTBOTTOM,
    RIGHTBOTTOM,
    RIGHTTOP,
    NONE
};
class note : public QDialog
{
    Q_OBJECT

public:
    explicit note();
    ~note();


private:

    void createAction();
    void contextMenuEvent(QContextMenuEvent *event);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void region(const QPoint &cursorPoint);
    void readFile(QString filename);
    QString getFileDateName();
public slots:
    void createNewNoteSlot();
    void saveNoteFileSlot();
    void deleteNoteSlot();
private:
    Ui::note *ui;
    QMenu *rightKeyMenu;
    QAction *newNoteAction;
    QAction *closeNoteAction;
    QAction *deleteNoteAction;
    QTextEdit *textexit;    //文本框
    bool isLeftPressDown;//左键是否按下
    QPoint dragPosition;//拖拽位置
    Direction dir; //方向
    QFile *file;
    QDateTime fileDate;
    QString fileName;
};

#endif // NOTE_H
