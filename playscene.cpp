#include "playscene.h"
#include "shapedwindow.h"
#include "mypushbutton.h"

/*
这是游戏场景，参数传进刚才选的武将和对手武将
*/
//这是暂停一段时间的函数
void playscene::stopforawhile(int times){
    //这里用了事件循环，日后可以学习一下
    QEventLoop loop;
    QTimer::singleShot(500*times, &loop, &QEventLoop::quit);
    loop.exec();
}

playscene::playscene(QString name1, QString name2, QWidget *parent)
    : QWidget(parent){
    //这好像是设置大小
    setFixedSize(1600,1200);
    //battelbgm=new QSound(":/playscene/res/start.wav",this);
    //battelbgm->setLoops(-1);
    //battelbgm->play();
    //设置英雄
    sethero(name1, 0);
    sethero(name2, 1);
    //设置卡槽
    setcardshop(0);
    setcardshop(1);
    //设置牌堆，随机生成53张牌
    for(int i=0; i<30; i++) cardheap[i] = new Sha;
    for(int i=30; i<45; i++) cardheap[i] = new Shan;
    for(int i=45; i<53; i++) cardheap[i] = new Tao;
    for(int i=53; i<55; i++) cardheap[i] = new AK;
    for(int i=55; i<58; i++) cardheap[i] = new Nanman;
    for(int i=58; i<59; i++) cardheap[i] = new Wanjian;
    srand(time(0));
    for(int i=0; i<59; i++){
        int j=rand()%59;
        Cards *p=cardheap[i];
        cardheap[i]=cardheap[j];
        cardheap[j]=p;
    }
    //初始化变量
    cardnum=0, mycardnum=0, enemycardnum=0;
    //双方摸4张牌
    for(int i=0; i<6; i++) mycardlist[i]=nullptr;
    for(int i=0; i<6; i++) enemycardlist[i]=nullptr;
    for(int i=0; i<4; i++) getcard(0);
    for(int i=0; i<4; i++) getcard(1);
    //我的回合开始
    connect(this, &playscene::mygamestart, [=](){
        //qDebug()<<mycardnum;
        QPixmap m(":/playscene/res/Botton.png");
        QLabel *newlabel=new QLabel(this);
        newlabel->setPixmap(m);
        newlabel->move(720,0);
        newlabel->show();
        delcard(0); //先把用完的牌清了
        for(int i=0; i<2; i++) getcard(0); //摸两张牌
        if(myhero->name=="GuoShen"){
            QSound *mus=new QSound(":/playscene/res/gschongzai.wav");
            mus->setLoops(1);
            mus->play();
        }
        for(int i=0; i<mycardnum; i++){
            //设置哪些牌能用
            if(mycardlist[i]->name=="Sha"){
                mycardlist[i]->canuse=1;
                mycardlist[i]->mask->hide();
            }
            if(mycardlist[i]->name=="Shan"){
                mycardlist[i]->canuse=0;
                mycardlist[i]->mask->show();
            }
            if(mycardlist[i]->name=="Tao"){
                if(myhero->hp==myhero->totalhp){
                    mycardlist[i]->canuse=0;
                    mycardlist[i]->mask->show();
                }
                else{
                    mycardlist[i]->canuse=1;
                    mycardlist[i]->mask->hide();
                }
            }
            if(mycardlist[i]->name=="AK"){
                mycardlist[i]->canuse=1;
                mycardlist[i]->mask->hide();
            }
            if(mycardlist[i]->name=="Nanman"){
                mycardlist[i]->canuse=1;
                mycardlist[i]->mask->hide();
            }
            if(mycardlist[i]->name=="Wanjian"){
                mycardlist[i]->canuse=1;
                mycardlist[i]->mask->hide();
            }
        }
        for(int i=0; i<mycardnum; i++){
            //设置出牌事件
            connect(mycardlist[i], &Cards::clicked, [=](){
                if(mycardlist[i]->canuse)
                    usecard(mycardlist[i], 0);
            });
        }
        //设置结束回合按钮
        MyPushButton *endturn = new MyPushButton(this,true,":/playscene/res/end1.png");
        endturn->move(this->width()-endturn->width(), 800);
        endturn->show();
        //设置结束回合事件
        connect(endturn, &MyPushButton::clicked, [=](){
            //删掉用过的牌
            delcard(0);
            //隐藏掉结束回合按钮
            endturn->hide();
            newlabel->hide();
            //进入我的弃牌阶段
            emit mythrowcard();
        });
    });
    //我的弃牌阶段开始
    connect(this, &playscene::mythrowcard, [=](){
        for(int i=0; i<mycardnum; i++){
            //弃牌阶段所有牌都可用（可弃）
            mycardlist[i]->canuse=1;
            mycardlist[i]->mask->hide();
        }
        //这是需要弃牌的数量
        thrownum = mycardnum-myhero->hp;
        QLabel *newlabel=new QLabel(this);
        if(thrownum==1){
            QPixmap m(":/playscene/res/Botton1.png");
            newlabel->setPixmap(m);
            newlabel->move(720,0);
            newlabel->show();
        }
        if(thrownum==2){
            QPixmap m(":/playscene/res/Botton2.png");
            newlabel->setPixmap(m);
            newlabel->move(720,0);
            newlabel->show();
        }
        if(thrownum==3){
            QPixmap m(":/playscene/res/Botton3.png");
            newlabel->setPixmap(m);
            newlabel->move(720,0);
            newlabel->show();
        }
        if(thrownum==4){
            QPixmap m(":/playscene/res/Botton4.png");
            newlabel->setPixmap(m);
            newlabel->move(720,0);
            newlabel->show();
        }
        if(thrownum==5){
            QPixmap m(":/playscene/res/Botton5.png");
            newlabel->setPixmap(m);
            newlabel->move(720,0);
            newlabel->show();
        }
        if(thrownum==6){
            QPixmap m(":/playscene/res/Botton6.png");
            newlabel->setPixmap(m);
            newlabel->move(720,0);
            newlabel->show();
        }
        if(thrownum<=0){
            QPixmap m(":/playscene/res/Botton0.png");
            newlabel->setPixmap(m);
            newlabel->move(720,0);
            newlabel->show();
        }
        for(int i=0; i<mycardnum; i++){
            //设置弃牌事件
            connect(mycardlist[i], &Cards::clicked, [=](){
                if(mycardlist[i]->canuse)
                    throwcard(mycardlist[i], 0);
            });
        }
        //设置结束弃牌阶段按钮
        MyPushButton *endthrow = new MyPushButton(this,true,":/playscene/res/end2.png");
        endthrow->move(this->width()-endthrow->width(), 800);
        endthrow->show();
        //设置结束弃牌阶段事件
        connect(endthrow, &MyPushButton::clicked, [=](){
            if(thrownum<=0){
                //删掉弃了的牌
                delcard(0);
                //隐藏按钮
                endthrow->hide();
                newlabel->hide();
                //对手回合开始
                for(int i=0;i<mycardnum;i++)
                    mycardlist[i]->mask->show();
                emit enemygamestart();
            }
        });
    });
    //对手回合开始
    connect(this, &playscene::enemygamestart, [=](){
        QPixmap m(":/playscene/res/EnemyBotton.png");
        QLabel *newlabel=new QLabel(this);
        newlabel->setPixmap(m);
        newlabel->move(720,0);
        newlabel->show();
        stopforawhile();
        delcard(1);
        //qDebug()<<"enemycardnum:"<<enemycardnum;
        for(int i=0; i<2; i++) getcard(1);
        if(enemyhero->name=="GuoShen"){
            QSound *mus=new QSound(":/playscene/res/gschongzai.wav");
            mus->setLoops(1);
            mus->play();
        }
        stopforawhile(2);
        //qDebug()<<"enemycardnum:"<<enemycardnum;
        for(int i=0; i<enemycardnum; i++){
            if(enemycardlist[i]->name=="Sha")
                enemycardlist[i]->canuse=1;
            if(enemycardlist[i]->name=="Shan")
                enemycardlist[i]->canuse=0;
            if(enemycardlist[i]->name=="Tao"){
                if(enemyhero->hp==enemyhero->totalhp) enemycardlist[i]->canuse=0;
                else enemycardlist[i]->canuse=1;
            }
            if(enemycardlist[i]->name=="AK")
                enemycardlist[i]->canuse=1;
            if(enemycardlist[i]->name=="Nanman")
                enemycardlist[i]->canuse=1;
            if(enemycardlist[i]->name=="Wanjian")
                enemycardlist[i]->canuse=1;
        }
        //qDebug()<<"enemycardnum:"<<enemycardnum;
        //qDebug()<<"cardnum:"<<cardnum;
        //直接出牌，先出杀再出桃，这里可以加个转场
        for(int i=0; i<enemycardnum; i++)
            if(enemycardlist[i]->name=="Tao" && enemycardlist[i]->canuse==true){
                usecard(enemycardlist[i], 1);
                stopforawhile(2);
                //stopforawhile();
            }
        for(int i=0; i<enemycardnum; i++){
            if(enemycardlist[i]->name=="AK" && enemycardlist[i]->canuse==true){
                usecard(enemycardlist[i], 1);
                stopforawhile(2);
            }
        }
        for(int i=0; i<enemycardnum; i++){
            if(enemycardlist[i]->name=="Sha" && enemycardlist[i]->canuse==true){
                usecard(enemycardlist[i], 1);
                stopforawhile();
            }
        }
        for(int i=0; i<enemycardnum; i++){
            if(enemycardlist[i]->name=="Nanman" && enemycardlist[i]->canuse==true){
                usecard(enemycardlist[i], 1);
                stopforawhile();
            }
        }
        for(int i=0; i<enemycardnum; i++){
            if(enemycardlist[i]->name=="Wanjian" && enemycardlist[i]->canuse==true){
                usecard(enemycardlist[i], 1);
                stopforawhile();
            }
        }
        newlabel->hide();
        //stopforawhile();
        QPixmap m1(":/playscene/res/EnemyBotton1.png");
        QLabel *newlabel1=new QLabel(this);
        newlabel1->setPixmap(m1);
        newlabel1->move(720,0);
        newlabel1->show();
        stopforawhile(2);
        delcard(1);
        //直接进入弃牌，这里可以加个转场
        for(int i=0; i<enemycardnum; i++){
            enemycardlist[i]->canuse=1;
        }
        thrownum = enemycardnum-enemyhero->hp;
        for(int i=0; i<enemycardnum; i++)
            if(enemycardlist[i]->name=="Sha" && thrownum>0){
                throwcard(enemycardlist[i], 1);
                stopforawhile();
            }
        for(int i=0; i<enemycardnum; i++)
            if(enemycardlist[i]->name=="Nanman" && thrownum>0){
                throwcard(enemycardlist[i], 1);
                stopforawhile();
            }
        for(int i=0; i<enemycardnum; i++)
            if(enemycardlist[i]->name=="Wanjian" && thrownum>0){
                throwcard(enemycardlist[i], 1);
                stopforawhile();
            }
        for(int i=0; i<enemycardnum; i++)
            if(enemycardlist[i]->name=="Shan" && thrownum>0){
                throwcard(enemycardlist[i], 1);
                stopforawhile();
            }
        for(int i=0; i<enemycardnum; i++)
            if(enemycardlist[i]->name=="Tao" && thrownum>0){
                throwcard(enemycardlist[i], 1);
                stopforawhile();
            }
        for(int i=0; i<enemycardnum; i++)
            if(enemycardlist[i]->name=="AK" && thrownum>0){
                throwcard(enemycardlist[i], 1);
                stopforawhile();
            }
        delcard(1);
        stopforawhile(2);
        newlabel1->hide();
        //stopforawhile();
        //弃牌结束，我的回合开始
        emit mygamestart();
    });
    //我被杀的信号
    connect(this, &playscene::mybekill, [=](){
        //自动出闪：找一张闪出掉
        stopforawhile();
        if(enemyhero->name=="LuoTian"){
            QSound *mus=new QSound(":/playscene/res/ltjingjue.wav");
            mus->setLoops(1);
            mus->play();
            stopforawhile();
        }
        useshan=0;
        int totalshan=0;
        for(int i=0; i<mycardnum; i++)
            if(mycardlist[i]->name=="Shan")
                totalshan++;
        for(int i=0; i<mycardnum; i++){
            if(mycardlist[i]->name=="Shan"){
                if(enemyhero->name=="LuoTian" && totalshan>=2){
                    usecard(mycardlist[i], 0);
                    useshan++;
                    if(useshan==2) break;
                    stopforawhile();
                }
                if(enemyhero->name!="LuoTian"){
                    usecard(mycardlist[i], 0);
                    useshan=1;
                    break;
                }
            }
        }
        delcard(0);
        //要是没出就掉血
        if(useshan==0){
            if(enemyhero->name=="YinShaofeng"){
                int opt = rand()%2;
                if(opt==1){
                    QSound *mus=new QSound(":/playscene/res/ysfma.wav");
                    mus->setLoops(1);
                    mus->play();
                }
                else{
                    QSound *mus=new QSound(":/playscene/res/ysfzhong.wav");
                    mus->setLoops(1);
                    mus->play();
                    myhero->sethp(myhero->hp-2);
                }
            }
            else myhero->sethp(myhero->hp-1);
            //掉血之后判定死没死
            if(myhero->hp<=0){
                stopforawhile(1);
                emit enemywin();
            }
        }
        stopforawhile();
    });
    connect(this, &playscene::mybenanman, [=](){
        //自动出闪：找一张闪出掉
        stopforawhile();
        if(myhero->name=="QinYiming"){
            QSound *mus=new QSound(":/playscene/res/qymweixiao.wav");
            mus->setLoops(1);
            mus->play();
            stopforawhile();
        }
        else{
            useshan=0;
            for(int i=0; i<mycardnum; i++){
                if(mycardlist[i]->name=="Sha"){
                    //usecard(mycardlist[i],1);
                    mycardlist[i]->isdel=true;
                    mycardlist[i]->canuse=false;
                    mycardlist[i]->hide();
                    QPixmap m(":playscene/res/Sha");
                    QLabel *newlabel=new QLabel(this);
                    newlabel->setPixmap(m);
                    newlabel->move(750,450);
                    newlabel->show();
                    QSound *mus=new QSound(":/playscene/res/sha.wav");
                    mus->setLoops(1);
                    mus->play();
                    //QTimer::singleShot(500,[=](){newlabel->hide();});
                    stopforawhile();
                    //
                    newlabel->hide();
                    useshan=1;
                    break;
                }
            }
            delcard(0);
            //要是没出就掉血
            if(useshan==0){
                myhero->sethp(myhero->hp-1);
                //掉血之后判定死没死
                if(myhero->hp<=0){
                    stopforawhile(1);
                    emit enemywin();
                }
            }
        }
        stopforawhile();
    });
    connect(this, &playscene::mybewanjian, [=](){
        //自动出闪：找一张闪出掉
        stopforawhile();
        if(myhero->name=="QinYiming"){
            QSound *mus=new QSound(":/playscene/res/qymweixiao.wav");
            mus->setLoops(1);
            mus->play();
            stopforawhile();
        }
        else{
            useshan=0;
            for(int i=0; i<mycardnum; i++){
                if(mycardlist[i]->name=="Shan"){
                    //usecard(mycardlist[i],1);
                    usecard(mycardlist[i], 0);
                    useshan=1;
                    break;
                }
            }
            delcard(0);
            //要是没出就掉血
            if(useshan==0){
                myhero->sethp(myhero->hp-1);
                //掉血之后判定死没死
                if(myhero->hp<=0){
                    stopforawhile(1);
                    emit enemywin();
                }
            }
        }
        stopforawhile();
    });
    //对手被杀的信号，和上面完全一致
    connect(this, &playscene::enemybekill, [=](){
        stopforawhile();
        if(myhero->name=="LuoTian"){
            QSound *mus=new QSound(":/playscene/res/ltjingjue.wav");
            mus->setLoops(1);
            mus->play();
            stopforawhile();
        }
        useshan=0;
        int totalshan=0;
        for(int i=0; i<enemycardnum; i++)
            if(enemycardlist[i]->name=="Shan")
                totalshan++;
        for(int i=0; i<enemycardnum; i++){
            if(enemycardlist[i]->name=="Shan"){
                if(myhero->name=="LuoTian" && totalshan>=2){
                    usecard(enemycardlist[i], 1);
                    useshan++;
                    if(useshan==2) break;
                    stopforawhile();
                }
                if(myhero->name!="LuoTian"){
                    usecard(enemycardlist[i], 1);
                    useshan=1;
                    break;
                }
            }
        }
        delcard(1);
        if(useshan==0){
            if(myhero->name=="YinShaofeng"){
                int opt = rand()%2;
                if(opt==1){
                    QSound *mus=new QSound(":/playscene/res/ysfma.wav");
                    mus->setLoops(1);
                    mus->play();
                }
                else{
                    QSound *mus=new QSound(":/playscene/res/ysfzhong.wav");
                    mus->setLoops(1);
                    mus->play();
                    enemyhero->sethp(enemyhero->hp-2);
                }
            }
            else enemyhero->sethp(enemyhero->hp-1);
            if(enemyhero->hp<=0){
                stopforawhile(1);
                emit mywin();
            }
        }
        stopforawhile();
    });
    connect(this, &playscene::enemybenanman, [=](){
        stopforawhile();
        if(enemyhero->name=="QinYiming"){
            QSound *mus=new QSound(":/playscene/res/qymweixiao.wav");
            mus->setLoops(1);
            mus->play();
            stopforawhile();
        }
        else{
            useshan=0;
            for(int i=0; i<enemycardnum; i++){
                if(enemycardlist[i]->name=="Sha"){
                    //usecard(mycardlist[i],1);
                    enemycardlist[i]->isdel=true;
                    enemycardlist[i]->canuse=false;
                    enemycardlist[i]->hide();
                    QPixmap m(":playscene/res/Sha");
                    QLabel *newlabel=new QLabel(this);
                    newlabel->setPixmap(m);
                    newlabel->move(750,450);
                    newlabel->show();
                    QSound *mus=new QSound(":/playscene/res/sha.wav");
                    mus->setLoops(1);
                    mus->play();
                    //QTimer::singleShot(500,[=](){newlabel->hide();});
                    stopforawhile();
                    //
                    newlabel->hide();
                    useshan=1;
                    break;
                }
            }
            delcard(1);
            if(useshan==0){
                enemyhero->sethp(enemyhero->hp-1);
                if(enemyhero->hp<=0){
                    stopforawhile(1);
                    emit mywin();
                }
            }
        }
        stopforawhile();
    });
    connect(this, &playscene::enemybewanjian, [=](){
        stopforawhile();
        if(enemyhero->name=="QinYiming"){
            QSound *mus=new QSound(":/playscene/res/qymweixiao.wav");
            mus->setLoops(1);
            mus->play();
            stopforawhile();
        }
        else{
            useshan=0;
            for(int i=0; i<enemycardnum; i++){
                if(enemycardlist[i]->name=="Shan"){
                    usecard(enemycardlist[i], 1);
                    useshan=1;
                    break;
                }
            }
            delcard(1);
            if(useshan==0){
                enemyhero->sethp(enemyhero->hp-1);
                if(enemyhero->hp<=0){
                    stopforawhile(1);
                    emit mywin();
                }
            }
        }
        stopforawhile();
    });
}

//弃牌函数，在这里可以加动画（用前面的QPixmap或者QMovie或者QPainter啥的方法）
void playscene::throwcard(Cards *card, bool player){
    QPixmap m(":playscene/res/"+card->name);
    QLabel *newlabel=new QLabel(this);
    newlabel->setPixmap(m);
    newlabel->move(750,450);
    QPixmap maskpic(":/playscene/res/mask.png"); //遮罩图像
    QLabel *mask = new QLabel(newlabel); //遮罩是一个QLabel类的对象（这个类一般用来创建图片）
    mask->resize(maskpic.size()); //调整大小
    mask->setStyleSheet("border-image:url(:/playscene/res/mask.png);"); //不知道是干啥的
    mask->show(); //初始隐藏遮罩
    newlabel->show();
    stopforawhile();
    newlabel->hide();
    mask->hide();
    if(player==0){
        //把这张牌删了
        card->isdel=true;
        card->canuse=false;
        card->hide();
        //重新设置每张牌的位置
        //为什么要这样：如果在这直接del了那张牌，前面的connect就会出bug
        for(int i=0,k=0; i<mycardnum; i++){
            if(mycardlist[i]->isdel==false){
                mycardlist[i]->move(120*k,5);
                mycardlist[i]->show();
                k++;
            }
        }
        thrownum--;
    }
    //对手弃牌，同上
    else{
        card->isdel=true;
        card->canuse=false;
        card->hide();
        for(int i=0,k=0; i<enemycardnum; i++){
            if(enemycardlist[i]->isdel==false){
                enemycardlist[i]->move(120*k,5);
                enemycardlist[i]->show();
                k++;
            }
        }
        thrownum--;
    }
}

void playscene::delcard(bool player){
    //删除我用过的牌，这里会重置所有connect
    if(player==0){
        //采用新建一个数组->把原来数组里没删的复制过去->把新数组复制到原数组的方法
        int lasnum=0;
        Cards *tmpcardlist[6];
        for(int i=0; i<mycardnum; i++)
            if(mycardlist[i]->isdel==false)
                tmpcardlist[lasnum++] = mycardlist[i];
        for(int i=0; i<6; i++){
            if(mycardlist[i]!=nullptr)
                mycardlist[i]->hide(),mycardlist[i]->disconnect();
            mycardlist[i]=nullptr;
        }
        mycardnum=lasnum;
        for(int i=0; i<mycardnum; i++){
            mycardlist[i]=tmpcardlist[i];
            mycardlist[i]->move(120*i,5);
            mycardlist[i]->show();
        }
    }
    //删除对方用过的牌，同上
    else{
        int lasnum=0;
        Cards *tmpcardlist[6];
        for(int i=0; i<enemycardnum; i++)
            if(enemycardlist[i]->isdel==false)
                tmpcardlist[lasnum++] = enemycardlist[i];
        for(int i=0; i<6; i++){
            if(enemycardlist[i]!=nullptr)
                enemycardlist[i]->hide(),enemycardlist[i]->disconnect();
            enemycardlist[i]=nullptr;
        }
        enemycardnum=lasnum;
        for(int i=0; i<enemycardnum; i++){
            enemycardlist[i]=tmpcardlist[i];
            enemycardlist[i]->move(120*i,5);
            enemycardlist[i]->show();
        }
    }
}

void playscene::usecard(Cards *card, bool player){
    if(player==0){
        card->isdel=true;
        card->canuse=false;
        card->hide();
        //挪后面牌的位置，实现“点掉一张牌”的功能
        for(int i=0,k=0; i<mycardnum; i++){
            if(mycardlist[i]->isdel==false){
                mycardlist[i]->move(120*k,5);
                mycardlist[i]->show();
                k++;
            }
        }
        //如果是杀，那么手里的其他杀都不能用
        if(card->name=="Sha"){
            for(int i=0; i<mycardnum; i++){
                if(mycardlist[i]->name=="Sha" && myhero->armedak==0){
                    mycardlist[i]->canuse=false;
                    mycardlist[i]->mask->show();
                }
            }
            QPixmap m(":/playscene/res/Sha");
            QLabel *newlabel=new QLabel(this);
            newlabel->setPixmap(m);
            newlabel->move(750,450);
            newlabel->show();
            QSound *mus=new QSound(":/playscene/res/sha.wav");
            mus->setLoops(1);
            mus->play();
            stopforawhile();
            newlabel->hide();
            emit enemybekill();
        }

        if(card->name=="Shan"){
            QPixmap m(":playscene/res/Shan");
            QLabel *newlabel=new QLabel(this);
            newlabel->setPixmap(m);
            newlabel->move(750,450);
            newlabel->show();
            QSound *mus=new QSound(":/playscene/res/shan.wav");
            mus->setLoops(1);
            mus->play();
            //QTimer::singleShot(500,[=](){newlabel->hide();});
            stopforawhile();
            //
            newlabel->hide();
        }
        //如果是桃，回一滴血
        if(card->name=="Tao"){
            QPixmap m(":playscene/res/Tao");
            QLabel *newlabel=new QLabel(this);
            newlabel->setPixmap(m);
            newlabel->move(750,450);
            newlabel->show();
            QSound *mus=new QSound(":/playscene/res/tao.wav");
            mus->setLoops(1);
            mus->play();
            stopforawhile();
            newlabel->hide();
            if(myhero->name=="YuWenkai"){
                QSound *mus=new QSound(":/playscene/res/ywkmiaoji.wav");
                mus->setLoops(1);
                mus->play();
                myhero->sethp(myhero->hp+2);
            }
            else myhero->sethp(myhero->hp+1);
        }
        if(card->name=="AK"){
            QPixmap m(":playscene/res/AK");
            QLabel *newlabel=new QLabel(this);
            newlabel->setPixmap(m);
            newlabel->move(750,450);
            newlabel->show();
            QSound *mus=new QSound(":/playscene/res/ak.wav");
            mus->setLoops(1);
            mus->play();
            stopforawhile();
            newlabel->hide();
            myhero->armak();
            QPixmap m1(":playscene/res/AKarmed");
            QLabel *newlabel1=new QLabel(this);
            newlabel1->setPixmap(m1);
            newlabel1->move(805,765);
            newlabel1->show();
        }
        if(card->name=="Nanman"){
            QPixmap m(":playscene/res/Nanman");
            QLabel *newlabel=new QLabel(this);
            newlabel->setPixmap(m);
            newlabel->move(750,450);
            newlabel->show();
            QSound *mus=new QSound(":/playscene/res/nanman.wav");
            mus->setLoops(1);
            mus->play();
            stopforawhile();
            newlabel->hide();
            emit enemybenanman();
        }
        if(card->name=="Wanjian"){
            QPixmap m(":playscene/res/Wanjian");
            QLabel *newlabel=new QLabel(this);
            newlabel->setPixmap(m);
            newlabel->move(750,450);
            newlabel->show();
            QSound *mus=new QSound(":/playscene/res/wanjian.wav");
            mus->setLoops(1);
            mus->play();
            stopforawhile();
            newlabel->hide();
            emit enemybewanjian();
        }
        //把当前牌标记为删除
        for(int i=0; i<mycardnum; i++){
            if(mycardlist[i]->name=="Tao"){
                if(myhero->hp==myhero->totalhp){
                    mycardlist[i]->canuse=0;
                    mycardlist[i]->mask->show();
                }
                else{
                    mycardlist[i]->canuse=1;
                    mycardlist[i]->mask->hide();
                }
            }
        }
    }
    else{
        card->isdel=true;
        card->canuse=false;
        card->hide();
        for(int i=0,k=0; i<enemycardnum; i++){
            if(enemycardlist[i]->isdel==false){
                enemycardlist[i]->move(120*k,5);
                enemycardlist[i]->show();
                k++;
            }
        }
        if(card->name=="Sha"){
            for(int i=0; i<enemycardnum; i++)
                if(enemycardlist[i]->name=="Sha" && enemyhero->armedak==0){
                    enemycardlist[i]->canuse=false;
                }
            QPixmap m(":playscene/res/Sha");
            QLabel *newlabel=new QLabel(this);
            newlabel->setPixmap(m);
            newlabel->move(750,450);
            newlabel->show();
            QSound *mus=new QSound(":/playscene/res/sha.wav");
            mus->setLoops(1);
            mus->play();
            stopforawhile();
            newlabel->hide();
            emit mybekill();
        }
        if(card->name=="Shan"){
            QPixmap m(":playscene/res/Shan");
            QLabel *newlabel=new QLabel(this);
            newlabel->setPixmap(m);
            newlabel->move(750,450);
            newlabel->show();
            QSound *mus=new QSound(":/playscene/res/shan.wav");
            mus->setLoops(1);
            mus->play();
            stopforawhile();
            newlabel->hide();
        }
        if(card->name=="Tao"){
            QPixmap m(":playscene/res/Tao");
            QLabel *newlabel=new QLabel(this);
            newlabel->setPixmap(m);
            newlabel->move(750,450);
            newlabel->show();
            QSound *mus=new QSound(":/playscene/res/tao.wav");
            mus->setLoops(1);
            mus->play();
            stopforawhile();
            newlabel->hide();
            if(enemyhero->name=="YuWenkai"){
                QSound *mus=new QSound(":/playscene/res/ywkmiaoji.wav");
                mus->setLoops(1);
                mus->play();
                enemyhero->sethp(enemyhero->hp+2);
            }
            else enemyhero->sethp(enemyhero->hp+1);
        }
        if(card->name=="AK"){
            QPixmap m(":playscene/res/AK");
            QLabel *newlabel=new QLabel(this);
            newlabel->setPixmap(m);
            newlabel->move(750,450);
            newlabel->show();
            QSound *mus=new QSound(":/playscene/res/ak.wav");
            mus->setLoops(1);
            mus->play();
            stopforawhile();
            newlabel->hide();
            enemyhero->armak();
            QPixmap m1(":playscene/res/AKarmed");
            QLabel *newlabel1=new QLabel(this);
            newlabel1->setPixmap(m1);
            newlabel1->move(305,295);
            newlabel1->show();
        }
        if(card->name=="Nanman"){
            QPixmap m(":playscene/res/Nanman");
            QLabel *newlabel=new QLabel(this);
            newlabel->setPixmap(m);
            newlabel->move(750,450);
            newlabel->show();
            QSound *mus=new QSound(":/playscene/res/nanman.wav");
            mus->setLoops(1);
            mus->play();
            stopforawhile();
            newlabel->hide();
            emit mybenanman();
        }
        if(card->name=="Wanjian"){
            QPixmap m(":playscene/res/Wanjian");
            QLabel *newlabel=new QLabel(this);
            newlabel->setPixmap(m);
            newlabel->move(750,450);
            newlabel->show();
            QSound *mus=new QSound(":/playscene/res/wanjian.wav");
            mus->setLoops(1);
            mus->play();
            stopforawhile();
            newlabel->hide();
            emit mybewanjian();
        }
        for(int i=0; i<enemycardnum; i++){
            if(enemycardlist[i]->name=="Tao"){
                if(enemyhero->hp==enemyhero->totalhp) enemycardlist[i]->canuse=0;
                else enemycardlist[i]->canuse=1;
            }
        }
    }
}

//这是摸牌，可以添加动画
void playscene::getcard(bool player){
    if(player==0){
        if(cardheap[cardnum]->name == QString("Sha")){
            mycardlist[mycardnum] = new Sha(0, mycardshop);
            if(myhero->name=="GuoShen") mycardlist[mycardnum]->name="Shan";
        }
        if(cardheap[cardnum]->name == QString("Shan")){
            mycardlist[mycardnum] = new Shan(0, mycardshop);
            if(myhero->name=="GuoShen") mycardlist[mycardnum]->name="Sha";
        }
        if(cardheap[cardnum]->name == QString("Tao"))
            mycardlist[mycardnum] = new Tao(0, mycardshop);
        if(cardheap[cardnum]->name == QString("AK"))
            mycardlist[mycardnum] = new AK(0, mycardshop);
        if(cardheap[cardnum]->name == QString("Nanman"))
            mycardlist[mycardnum] = new Nanman(0, mycardshop);
        if(cardheap[cardnum]->name == QString("Wanjian"))
            mycardlist[mycardnum] = new Wanjian(0, mycardshop);
        mycardlist[mycardnum]->move(120*mycardnum,5);
        mycardlist[mycardnum]->show();
        cardnum++, cardnum=cardnum%59, mycardnum++;
    }
    else{/*
        简单模式：对手只有杀
        enemycardlist[enemycardnum] = new Sha(1, enemycardshop);
        enemycardlist[enemycardnum]->move(120*enemycardnum,5);
        enemycardlist[enemycardnum]->show();
        enemycardnum++;
        */
        /*苦难模式：正常*/
        if(cardheap[cardnum]->name == QString("Sha")){
            enemycardlist[enemycardnum] = new Sha(1, enemycardshop);
            if(enemyhero->name=="GuoShen") enemycardlist[enemycardnum]->name="Shan";
        }
        if(cardheap[cardnum]->name == QString("Shan")){
            enemycardlist[enemycardnum] = new Shan(1, enemycardshop);
            if(enemyhero->name=="GuoShen") enemycardlist[enemycardnum]->name="Sha";
        }
        if(cardheap[cardnum]->name == QString("Tao"))
            enemycardlist[enemycardnum] = new Tao(1, enemycardshop);
        if(cardheap[cardnum]->name == QString("AK"))
            enemycardlist[enemycardnum] = new AK(1, enemycardshop);
        if(cardheap[cardnum]->name == QString("Nanman"))
            enemycardlist[enemycardnum] = new Nanman(1, enemycardshop);
        if(cardheap[cardnum]->name == QString("Wanjian"))
            enemycardlist[enemycardnum] = new Wanjian(1, enemycardshop);
        enemycardlist[enemycardnum]->move(120*enemycardnum,5);
        enemycardlist[enemycardnum]->show();
        cardnum++, cardnum=cardnum%59, enemycardnum++;
    }
}

//设置武将
void playscene::sethero(QString name, bool player){
    if(player==0){
        if(name=="GuoShen") myhero = new GuoShen(player, this);
        if(name=="YuWenkai") myhero = new YuWenkai(player, this);
        if(name=="YinShaofeng") myhero = new YinShaofeng(player, this);
        if(name=="QinYiming") myhero = new QinYiming(player, this);
        if(name=="LuoTian") myhero = new LuoTian(player, this);
    }
    else{
        if(name=="GuoShen") enemyhero = new GuoShen(player, this);
        if(name=="YuWenkai") enemyhero = new YuWenkai(player, this);
        if(name=="YinShaofeng") enemyhero = new YinShaofeng(player, this);
        if(name=="QinYiming") enemyhero = new QinYiming(player, this);
        if(name=="LuoTian") enemyhero = new LuoTian(player, this);
    }
}

//设置卡槽
void playscene::setcardshop(bool player){
    if(player==0){
        //这是卡槽图像
        QPixmap mycardpic(":/playscene/res/Cardshop.png");
        mycardshop = new QLabel(this);
        mycardshop->resize(mycardpic.size());
        mycardshop->setPixmap(mycardpic);
        mycardshop->move(800, 900);
        mycardshop->show();
    }
    else{
        QPixmap enemycardpic(":/playscene/res/Cardshop.png");
        enemycardshop = new QLabel(this);
        enemycardshop->resize(enemycardpic.size());
        enemycardshop->setPixmap(enemycardpic);
        enemycardshop->move(300, 0);
        enemycardshop->show();
    }
}

//这是绘制游戏背景
void playscene::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    //这是背景图像路径
    QImage bg(":/playscene/res/playscenebg.png");
    bg=bg.scaled(size(),Qt::KeepAspectRatioByExpanding);
    painter.drawImage(-250,0,bg);
}
