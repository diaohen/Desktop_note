#include "note.h"
#include "ui_note.h"

note::note() : QDialog(),ui(new Ui::note)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog | Qt::Window |
                   Qt::Desktop  | Qt::WindowMinimizeButtonHint);
    //Qt::WindowStaysOnTopHint 窗体置顶
    //Qt::FramelessWindowHint 无边框窗体
    fileName = getFileDateName();
    readFile(fileName);
    isLeftPressDown = false;
    this->setMouseTracking(true);//鼠标跟踪
    createAction();
    //connect(ui->textEdit,SIGNAL())
    connect(ui->textEdit,SIGNAL(textChanged()),SLOT(saveNoteFileSlot()));
}
//最小任务栏
//文件读写
//便签管理器   便签的分类
//配置文件（便签个数，位置，大小，颜色，透明度，背景图片，甚至是便签内容）
note::~note()
{
    delete ui;
}
QString note::getFileDateName()
{
    fileDate = QDateTime::currentDateTime();
    QString fileName = fileDate.toString("yyyy-MM-dd-hh-mm-ss");
    return fileName;
}
void note::createAction()//创建右键菜单
{
    rightKeyMenu = new QMenu();
    newNoteAction = new QAction(tr("新建便签"), this);
    closeNoteAction = new QAction(tr("关闭便签"),this);
    deleteNoteAction = new QAction(tr("删除便签"),this);
    connect(newNoteAction,SIGNAL(triggered()),this,SLOT(createNewNoteSlot()));
    connect(closeNoteAction,SIGNAL(triggered()),this,SLOT(close()));
    connect(deleteNoteAction,SIGNAL(triggered()),this,SLOT(deleteNoteSlot()));

}
void note::deleteNoteSlot()
{
    file->remove(fileName);
    this->close();

}
void note::contextMenuEvent(QContextMenuEvent *event)//将Action添加到菜单上
{
    //rightKeyMenu->clear();
    rightKeyMenu->addAction(newNoteAction);
    rightKeyMenu->addAction(closeNoteAction);
    rightKeyMenu->addAction(deleteNoteAction);
    rightKeyMenu->exec(QCursor::pos());
    event->accept();
}
void note::createNewNoteSlot()//右键菜单，新建一个便签
{
    note *newNote1 = new note();
    newNote1->show();
}

void note::mouseReleaseEvent(QMouseEvent *event)//重写鼠标释放事件
{
    if(event->button() == Qt::LeftButton) {
        isLeftPressDown = false;
        if(dir != NONE) {
            this->releaseMouse();
            this->setCursor(QCursor(Qt::ArrowCursor));
        }
    }
}

void note::mousePressEvent(QMouseEvent *event)//重写鼠标按下事件
{
    switch(event->button()) {
    case Qt::LeftButton:
        isLeftPressDown = true;
        if(dir != NONE) {
            this->mouseGrabber();
        } else {
            dragPosition = event->globalPos() - this->frameGeometry().topLeft();
        }
        break;
    case Qt::RightButton:
        createAction();
        //this->close();
        break;
    default:
        QDialog::mousePressEvent(event);
    }

}

void note::mouseMoveEvent(QMouseEvent *event)//重写鼠标移动事件
{
    QPoint gloPoint = event->globalPos();
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    if(!isLeftPressDown) {
        this->region(gloPoint);
    } else {

        if(dir != NONE) {
            QRect rMove(tl, rb);

            switch(dir) {
            case LEFT:
                if(rb.x() - gloPoint.x() <= this->minimumWidth())
                    rMove.setX(tl.x());
                else
                    rMove.setX(gloPoint.x());
                break;
            case RIGHT:
                rMove.setWidth(gloPoint.x() - tl.x());
                break;
            case UP:
                if(rb.y() - gloPoint.y() <= this->minimumHeight())
                    rMove.setY(tl.y());
                else
                    rMove.setY(gloPoint.y());
                break;
            case DOWN:
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            case LEFTTOP:
                if(rb.x() - gloPoint.x() <= this->minimumWidth())
                    rMove.setX(tl.x());
                else
                    rMove.setX(gloPoint.x());
                if(rb.y() - gloPoint.y() <= this->minimumHeight())
                    rMove.setY(tl.y());
                else
                    rMove.setY(gloPoint.y());
                break;
            case RIGHTTOP:
                rMove.setWidth(gloPoint.x() - tl.x());
                rMove.setY(gloPoint.y());
                break;
            case LEFTBOTTOM:
                rMove.setX(gloPoint.x());
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            case RIGHTBOTTOM:
                rMove.setWidth(gloPoint.x() - tl.x());
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            default:

                break;
            }
            this->setGeometry(rMove);
        } else {
            move(event->globalPos() - dragPosition);
            event->accept();
        }
    }
    QDialog::mouseMoveEvent(event);
}

void note::region(const QPoint &cursorGlobalPoint)//改变大小时，位置计算
{
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());
    int x = cursorGlobalPoint.x();
    int y = cursorGlobalPoint.y();

    if(tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y) {
        // 左上角
        dir = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    } else if(x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y()) {
        // 右下角
        dir = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    } else if(x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y()) {
        //左下角
        dir = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING) {
        // 右上角
        dir = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= tl.x() + PADDING && x >= tl.x()) {
        // 左边
        dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    } else if( x <= rb.x() && x >= rb.x() - PADDING) {
        // 右边
        dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }else if(y >= tl.y() && y <= tl.y() + PADDING){
        // 上边
        dir = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    } else if(y <= rb.y() && y >= rb.y() - PADDING) {
        // 下边
        dir = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }else {
        // 默认
        dir = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}


void note::saveNoteFileSlot()
{
    //ui->textEdit->document()->isModified()//文字是否改变
    file = new QFile;
    file->setFileName(fileName);
    bool ok = file->open(QIODevice::WriteOnly);
    if(ok)
    {
        QTextStream out(file);
        out << ui->textEdit->toPlainText();
        file->close();
        delete file;
    }
    else
    {
        //QMessageBox::information(this,"Error Message","Save File Error");
    }
    return ;


}


void note::readFile(QString filename)
{
    file = new QFile;
    file->setFileName(filename);
    bool ok = file->open(QIODevice::ReadOnly);
    if(ok)
    {

        QTextStream in(file);
        QString text = filename + in.readAll();
        ui->textEdit->setText(text);
        file->close();
        delete file;
    }
    else
    {
        //QMessageBox::information(this,"Error Message","read File Error !");
    }
}









