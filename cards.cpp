#include "cards.h"

/*
这是卡牌类
name是名字，hide表示这张牌是否不能展示给玩家
parent是QWidget组件，表示该组件的父组件
比如我的卡牌的父组件就是我的卡槽，我的卡牌只能显示在卡槽范围里，出去的话就没了
*/
Cards::Cards(QString name, bool hide, QWidget *parent)
    : QPushButton(parent), name(name){ //卡牌是个按钮，故继承QPushButton，先调用父类的复制构造函数
    setCursor(Qt::PointingHandCursor); //设置鼠标放在按钮上变成的图像（这是个手指图像）
    //根据hide情况加载图像
    if(!hide) picture.load(":/playscene/res/"+name+".png");
    else picture.load(":playscene/res/Card.png");
    setFixedSize(picture.width(),picture.height()); //设置图像尺寸
    setMask(picture.mask()); //设置遮罩
    setStyleSheet("QPushButton{border:0px;}"); //调整无边框
    QPainter painter(&picture); //绘制图像
    //调整图片大小，这0.7似乎是参数，凯哥可以调一下逝逝
    QPixmap picc(name);
    picc=picc.scaled(picture.size()*0.7,Qt::KeepAspectRatio);
    //绘制卡牌图像
    painter.drawPixmap((picture.width()-picc.width())*0.5,15,picc.width(),picc.height(),picc);
    setIcon(picture); //设置按钮图像为卡牌图像
    setIconSize(QSize(picture.width(),picture.height())); //设置按钮大小跟卡牌图像大小一样
    //设置遮罩
    QPixmap maskpic(":/playscene/res/mask.png"); //遮罩图像
    mask=new QLabel(this); //遮罩是一个QLabel类的对象（这个类一般用来创建图片）
    mask->resize(maskpic.size()); //调整大小
    mask->setStyleSheet("border-image:url(:/playscene/res/mask.png);"); //不知道是干啥的
    mask->hide(); //初始隐藏遮罩
}

void Cards::mousePressEvent(QMouseEvent *e){
    //如果没有遮罩才能点动
    if(mask->isHidden()) return QPushButton::mousePressEvent(e);
    //有遮罩就点不动
    else e->ignore();
}

//以下是各个子类卡牌的构造函数
Sha::Sha(bool hide, QWidget *parent) : Cards("Sha", hide, parent){}
Shan::Shan(bool hide, QWidget *parent) : Cards("Shan", hide, parent){}
Tao::Tao(bool hide, QWidget *parent) : Cards("Tao", hide, parent){}
AK::AK(bool hide, QWidget *parent) : Cards("AK", hide, parent){}
Nanman::Nanman(bool hide, QWidget *parent) : Cards("Nanman", hide, parent){}
Wanjian::Wanjian(bool hide, QWidget *parent) : Cards("Wanjian", hide, parent){}
