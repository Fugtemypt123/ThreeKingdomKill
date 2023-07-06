#include "choosemenu.h"

/*
这是选人界面
接受三个参数：待选择的两个武将的名字，以及该窗口的父组件
*/
ChooseMenu::ChooseMenu(QString h1name, QString h2name, QWidget *parent)
    : QWidget(parent){
    //选人界面的bgm，可以调整
    //bgm=new QSound(":/menu/res/start.wav"); //音频文件路径
    //bgm->setLoops(-1); //设置无限循环bgm
    //bgm->play(); //播放
    //英雄1按钮设置
    MyPushButton* hero1=new MyPushButton(this,true,":/menu/res/"+(h1name)+".png"); //图像文件路径
    hero1->move(300,580); //这是该按钮在窗口所处的位置
    connect(hero1,&MyPushButton::clicked,[=](){
        //bgm->stop();
        emit choosehero1();
    });
    //英雄2按钮设置
    MyPushButton* hero2=new MyPushButton(this,true,":/menu/res/"+(h2name)+".png"); //图像文件路径
    hero2->move(1000,580); //这是该按钮在窗口所处的位置
    connect(hero2,&MyPushButton::clicked,[=](){
        //bgm->stop();
        emit choosehero2();
    });
}

//背景图片设置（这是设置背景图片的通用方法）
void ChooseMenu::paintEvent(QPaintEvent *event){
    QPainter painter(this); //绘图事件
    QImage bg(":/menu/res/choosemenubg.png"); //图像文件路径
    //bg=bg.scaled(size(),Qt::KeepAspectRatioByExpanding); //调整大小，这应该是自动伸缩适应窗口
    painter.drawImage(0,0,bg); //绘图
}


