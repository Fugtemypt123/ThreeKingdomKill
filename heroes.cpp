#include "heroes.h"

/*
这是武将类
name是名字，hp是血量=血量上限，player是玩家（决定英雄显示位置）
*/
Heroes::Heroes(QString name, int hp, bool player, QWidget *parent)
    : QLabel(parent), name(name), hp(hp), totalhp(hp){ //武将就是个图片不是按钮，故继承QLabel
    //设置图像
    picture.load(":/playscene/res/"+name+".png"); //武将图片
    //setFixedSize(900,700); //调整武将牌大小
    setPixmap(picture); //设置图像
    //根据玩家决定武将牌摆放位置
    if(player==0) move(500, 780);
    else move(0, 0);
    show(); //展示图像
    armedak = 0;
    //设置血量
    QPixmap mypic(":/playscene/res/hp.png"); //单个血量的图片
    //把单个血量重复hp次变成hp个血量
    for(int i=0; i<hp; i++){
        hppic[i] = new QLabel(this);
        hppic[i]->resize(mypic.size());
        hppic[i]->setPixmap(mypic);
        hppic[i]->move(0, i*20); //这是调整位置的函数
        hppic[i]->show();
    }
    setAttribute(Qt::WA_TransparentForMouseEvents, true); //不要遮挡下面的控件
}

//以下是各个子类武将的构造函数
GuoShen::GuoShen(bool player, QWidget *parent):Heroes("GuoShen", 4, player, parent){}
YuWenkai::YuWenkai(bool player, QWidget *parent):Heroes("YuWenkai", 3, player, parent){}
YinShaofeng::YinShaofeng(bool player, QWidget *parent):Heroes("YinShaofeng", 4, player, parent){}
QinYiming::QinYiming(bool player, QWidget *parent):Heroes("QinYiming", 4, player, parent){}
LuoTian::LuoTian(bool player, QWidget *parent):Heroes("LuoTian", 3, player, parent){}

//设置武将血量为某一值
void Heroes::sethp(int nowhp){
    //如果超过上限则变成上限
    if(nowhp>totalhp) nowhp=totalhp;
    //重新加载图片，同上
    if(nowhp<hp){
        QSound *hurtbgm = new QSound(":/playscene/res/hurt.wav",this);
        hurtbgm->setLoops(1);
        hurtbgm->play();
    }
    QPixmap mypic(":/playscene/res/hp.png");
    for(int i=0; i<hp; i++) hppic[i]->hide();
    for(int i=0; i<nowhp; i++){
        hppic[i] = new QLabel(this);
        hppic[i]->resize(mypic.size());
        hppic[i]->setPixmap(mypic);
        hppic[i]->move(0, i*20);
        hppic[i]->show();
    }
    hp=nowhp;
}

void Heroes::armak(){
    armedak = 1;
}
//以下是武将相关的动画
//暂停
/*
void Heroes::Hstop()
{
    movie->stop();
}

//恢复
void Heroes::Hstart()
{
    movie->start();
}
*/

//改变状态后，改变图片
/*
void Heroes::Change()
{
    switch(hp)
    {
        case 0:
        {
            HpPath=":/heroes/hp0.png";
            break;
        }
        case 1:
        {
            HpPath=":/heroes/hp1.png";
            break;
        }
        case 2:
        {
            HpPath=":/heroes/hp2.png";
            break;
        }
        case 3:
        {
            HpPath=":/heroes/hp3.png";
            break;
        }
        case 4:
        {
            HpPath=":/heroes/hp4.png";
            break;
        }
        default:break;
    }
    /*
    这里需要改成图片形式
    int n=movie->currentFrameNumber();
    delete movie;
    movie=new QMovie(WalkPath,QByteArray(),this);
    movie->setSpeed(WalkSpeed);
    this->setMovie(movie);
    movie->jumpToFrame(n);
    movie->start();
    this->show();
    }

}
*/

//受击
    /*
void Heroes::GetHurt(int attack)
{
    hp -= attack;
    //这里插入一个受击动画
}

//杀人
void Heroes::Attack(QString Gif)
{
    int n = 0;
    if(movie!=nullptr)
    {
        n = movie->currentFrameNumber();
        delete movie;
    }
    movie = new QMovie(Gif,QByteArray(),this);
    this->setMovie(movie);
    movie->jumpToFrame(n);
    movie->start();
    this->show();
}

//被杀
void Heroes::Hurt(QString Gif)
{
    int n = 0;
    if(movie!=nullptr)
    {
        n = movie->currentFrameNumber();
        delete movie;
    }
    movie = new QMovie(Gif,QByteArray(),this);
    this->setMovie(movie);
    movie->jumpToFrame(n);
    movie->start();
    this->show();
}

//死亡
void Heroes::Die(QString Gif)
{
    int n = 0;
    if(movie!=nullptr)
    {
        n = movie->currentFrameNumber();
        delete movie;
    }
    movie = new QMovie(Gif,QByteArray(),this);
    this->setMovie(movie);
    movie->jumpToFrame(n);
    movie->start();
    this->show();
}*/

