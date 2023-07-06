#include "endscene.h"
#include "shapedwindow.h"
#include "mypushbutton.h"
/*
这是游戏场景，参数传进刚才选的武将和对手武将
*/

endscene::endscene(bool player, QWidget *parent)
    : QWidget(parent){
    if(player==0){
        //这里是设置胜利图像
        MyPushButton *trophy=new MyPushButton(this,true,":/playscene/res/win.png");
        //trophy->setFixedSize()
        //trophy->move((width()-trophy->width())*0.5,(height()-trophy->height())*0.5);
        trophy->move(-60, -25);
        trophy->show();
        //这里是设置胜利图像弹出来的动画
        /*QPropertyAnimation *tanime=new QPropertyAnimation(trophy,"geometry",this);
        tanime->setStartValue(QRect((width()-trophy->width())*0.5,(height()-trophy->height())*0.5-50,trophy->width(),trophy->height()));
        tanime->setEndValue(QRect((width()-trophy->width())*0.5,(height()-trophy->height())*0.5,trophy->width(),trophy->height()));
        tanime->setEasingCurve(QEasingCurve::InBack);
        tanime->setDuration(500);
        tanime->start();*/
        //battelbgm->stop();
        //单击奖杯事件
        connect(trophy,&MyPushButton::clicked,[=](){
            //播放胜利音乐
            QSound *winbgm = new QSound(":/playscene/res/win.wav",this);
            winbgm->setLoops(1);
            winbgm->play();
            //单击1秒后弹出新窗口
            QTimer::singleShot(1000,[=](){ //这是一个计时器，1s后进入后面语句
                //这里是新窗口的图像
                ShapedWindow* win=new ShapedWindow(this,":/playscene/res/win1.png");
                win->move((this->width()-win->width())*0.5,(this->height()-win->height())*0.5);
                //这里是单击返回主菜单的按钮
                MyPushButton* yes=new MyPushButton(win,true,":/playscene/res/yesButton2.png");
                connect(yes,&MyPushButton::clicked,[=](){
                    emit mainmenu();
                });
                yes->move((win->width()-yes->width())*0.5-5,215);
                win->show();
            });
        });
    }
    //对手一方胜利
    else{
        //这里是设置胜利图像
        MyPushButton *trophy=new MyPushButton(this,true,":/playscene/res/lose.png");
        //trophy->move((width()-trophy->width())*0.5,(height()-trophy->height())*0.5);
        trophy->move(-75, 0);
        trophy->show();
        /*QPropertyAnimation *tanime=new QPropertyAnimation(trophy,"geometry",this);
        tanime->setStartValue(QRect((width()-trophy->width())*0.5,(height()-trophy->height())*0.5-50,trophy->width(),trophy->height()));
        tanime->setEndValue(QRect((width()-trophy->width())*0.5,(height()-trophy->height())*0.5,trophy->width(),trophy->height()));
        tanime->setEasingCurve(QEasingCurve::InBack);
        tanime->setDuration(500);
        tanime->start();*/
        //battelbgm->stop();
        connect(trophy,&MyPushButton::clicked,[=](){
            QSound *winbgm = new QSound(":/playscene/res/die.wav",this);
            winbgm->setLoops(1);
            winbgm->play();
            QTimer::singleShot(1000,[=](){
                ShapedWindow* lose=new ShapedWindow(this,":/playscene/res/lose1.png");
                //lose->setFixedSize(QSize(200, 300));
                lose->move((this->width()-lose->width())*0.5,(this->height()-lose->height())*0.5);
                MyPushButton* yes=new MyPushButton(lose,true,":/playscene/res/yesButton2.png");
                //yes->move(300,300);
                connect(yes,&MyPushButton::clicked,[=](){
                    emit mainmenu();
                });
                yes->move((lose->width()-yes->width())*0.5-5,215);
                lose->show();
            });
        });
    }
}
