#include "mymenu.h"

/*
这是开始界面（是界面，不是主窗口）
*/
MyMenu::MyMenu(QWidget *parent)
    : QWidget(parent){
    //bgm播放
    bgm=new QSound(":/menu/res/start.wav");
    bgm->setLoops(-1);
    bgm->play();
    //背景图像播放，这里是gif形式的写法
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel(this);
    layout->addWidget(label);
    QMovie *movie = new QMovie(":/menu/res/bg.gif");
    label->setMovie(movie);
    //label->setFixedSize(QSize(200, 200)); //这个是设置大小，好像没用
    movie->start();
    //开始游戏按钮设置
    MyPushButton *newgame = new MyPushButton(this,true,":/menu/res/newbutton1.png",":/menu/res/newbutton1.png");
    //newgame->setFixedSize(QSize(450, 450));
    newgame->move(1250,0);
    connect(newgame,&MyPushButton::clicked,[=](){
        //bgm->stop();
        emit chooseperson();
    });
    QLabel *starticon = new QLabel(label);
    QPixmap icon(":menu/res/starticon.png");
    icon = icon.scaled(icon.size()*0.5,Qt::KeepAspectRatio);
    starticon->setPixmap(icon);
    starticon->move(0,0);
    starticon->show();

    //退出按钮
    MyPushButton* quit=new MyPushButton(this,false,":/menu/res/newbutton3.png",":/menu/res/newbutton3.png");
    //quit->setFixedSize(QSize(450, 450));
    quit->move(1250,970);
    connect(quit,&MyPushButton::clicked,[=](){
        emit readyforquit();
    });
}

//背景图像播放，这里是png形式的写法
/*
void MyMenu::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QImage bg(":/menu/res/bg.png");
    bg=bg.scaled(size(),Qt::KeepAspectRatioByExpanding);
    painter.drawImage(0,0,bg);
}
*/

void MyMenu::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);
    // 获取窗口的大小
    QSize windowSize = event->size();
    // 获取背景标签的大小
    QLabel *backgroundLabel = findChild<QLabel *>();
    if (backgroundLabel){
        // 调整背景标签的大小和位置以适应窗口
        backgroundLabel->setGeometry(0, 0, windowSize.width(), windowSize.height());
        QMovie *movie = backgroundLabel->movie();
        if (movie){
            movie->setScaledSize(windowSize);
        }
    }
}

