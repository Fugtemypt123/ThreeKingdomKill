#ifndef CHOOSEMENU_H
#define CHOOSEMENU_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QSound>
#include <QMovie>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QResizeEvent>
#include "mypushbutton.h"
#include "heroes.h"

//这是选人界面
class ChooseMenu : public QWidget{
    Q_OBJECT
public:
    explicit ChooseMenu(QString h1name, QString h2name, QWidget *parent=0); //构造函数
    QSound* bgm; //选人界面的bgm，可以改成跟开始界面不一样的
    void paintEvent(QPaintEvent *event); //绘制图像

signals:
    void choosehero1(); //选择英雄1的信号
    void choosehero2(); //选择英雄2的信号

public slots:
};

#endif // CHOOSEMENU_H
