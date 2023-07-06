#include "shapedwindow.h"
#include "mypushbutton.h"

//这是自定义窗口类，可以不动
ShapedWindow::ShapedWindow(QWidget *parent,QString pix)
    : QMainWindow(parent){
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::FramelessWindowHint);
    QString tmp=QString("background-image:url(")+pix+QString(");");
    setStyleSheet(tmp);
    pixmap.load(pix);
    setMask(pixmap.mask());
    setFixedSize(pixmap.size());
}

void ShapedWindow::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        mousepos = event->globalPos(); //记录按下位置
        LeftBtnPress = true;
    }
    event->ignore();
}

//这个类支持移动窗口，虽然我们用不到
void ShapedWindow::mouseMoveEvent(QMouseEvent *event){
    if(LeftBtnPress){ //移动窗口
        move(pos() + event->globalPos() - mousepos);
        mousepos = event->globalPos();
    }
    event->ignore();
}

void ShapedWindow::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton)
        LeftBtnPress = false;
    event->ignore();
}
