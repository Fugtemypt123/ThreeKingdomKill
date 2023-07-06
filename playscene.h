#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QWidget>
#include <QSound>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QPainter>
#include "cards.h"
#include "heroes.h"
#include "mypushbutton.h"

//这是游戏场景
class playscene : public QWidget{
    Q_OBJECT
public:
    explicit playscene(QString name1, QString name2, QWidget *parent=0); //构造函数
    QSound *battelbgm; //游戏场景的bgm
    Cards *cardheap[59]; //牌堆，目前没图像，可以做个图像
    Cards *mycardlist[6]; //我的手牌
    Cards *enemycardlist[6]; //对手的手牌
    Heroes *myhero; //我的英雄
    Heroes *enemyhero; //对手的英雄
    QLabel *mycardshop; //我的卡槽
    QLabel *enemycardshop; //对手的卡槽
    int cardnum; //牌堆目前发到了第几张牌
    int mycardnum; //我的手牌有几张
    int enemycardnum; //对手的手牌有几张
    int thrownum; //需要弃牌的数目（这本来应该是个局部变量）
    //int inturn; //当前是谁的回合（目前没有任何作用）
    int useshan; //是否出了闪（这本来应该是个局部变量）
    void paintEvent(QPaintEvent *event); //绘图事件，用来绘制背景
    void sethero(QString name, bool player); //将选人界面选的英雄设置到游戏场景里
    void setcardshop(bool player); //设置player（我/对手）的卡槽
    void getcard(bool player); //player抽一张牌
    void delcard(bool player); //player删除掉所有弃过的牌
    void winning(bool player); //player胜利
    void usecard(Cards *card, bool player); //player用一张牌card
    void throwcard(Cards *card, bool player); //player弃一张牌card
    void stopforawhile(int times=1);
    QSound *winbgm=nullptr; //胜利bgm
    //复制上面的可以加一个失败bgm

signals:
    void mygamestart(); //我的出牌回合开始信号
    void enemygamestart(); //对手的出牌回合开始信号
    void mythrowcard(); //我的弃牌回合开始信号
    void enemythrowcard(); //对手的出牌回合开始信号
    void mybekill(); //我的被杀信号
    void enemybekill(); //对手的被杀信号
    void mybenanman();
    void enemybenanman();
    void mybewanjian();
    void enemybewanjian();
    //void mainmenu();  //回到主菜单信号（游戏结束）
    void menuclicked(); //单击菜单信号
    void mywin();
    void enemywin();

public slots:
};

#endif // PLAYSCENE_H
