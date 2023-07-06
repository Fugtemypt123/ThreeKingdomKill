#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shapedwindow.h"
#include "mypushbutton.h"

/*
这是游戏窗口
继承QMainWindow类，并且包含ui组件
ui->stackedWidget->setCurrentIndex()可以用来在各个界面间来回切换
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow){ //我没看懂这个ui是咋构造的，反正默认是这样
    //设置ui
    ui->setupUi(this);
    //setFixedSize(1600, 1200);
    setWindowIcon(QIcon(":/menu/res/AA.ico")); //这是游戏窗口左上角那个图片
    setWindowTitle("ThreeKingdomKill"); //这是游戏窗口的名字，也显示在左上角
    ui->stackedWidget->setCurrentIndex(0); //设置当前界面为0号界面
    //QSound *bgm=new QSound(":/menu/res/start.wav"); //音频文件路径
    //bgm->setLoops(-1); //设置无限循环bgm
    //bgm->play(); //播放
    //设置退出弹框+按钮
    connect(ui->menu, &MyMenu::readyforquit,[=](){
        //底下这些是文件路径和位置参数
        ShapedWindow *quitwindow = new ShapedWindow(this,":/menu/res/QuitWindow.png");
        quitwindow->move((this->width()-quitwindow->width())*0.5, (this->height()-quitwindow->height())*0.5);
        MyPushButton *quit = new MyPushButton(quitwindow,true,":/menu/res/QuitButton.png");
        connect(quit, &MyPushButton::clicked, [=](){
            this->close();
        });
        quit->move(40,210);
        MyPushButton *cancel = new MyPushButton(quitwindow,true,":/menu/res/CancelButton.png");
        connect(cancel, &MyPushButton::clicked, [=](){
            delete quitwindow;
        });
        cancel->move(270,210);
        quitwindow->show();
    });
    //设置选项界面
    connect(ui->menu, &MyMenu::optionclicked, [=](){
        //底下这些是文件路径和位置参数
        ShapedWindow *option = new ShapedWindow(this,":/menu/res/Options.png");
        option->move((this->width()-option->width())*0.5, (this->height()-option->height())*0.5);
        MyPushButton *yes = new MyPushButton(option,true,":/menu/res/yesButton.png");
        connect(yes, &MyPushButton::clicked, [=](){
            delete option;
        });
        yes->move((option->width()-yes->width())*0.5, 540);
        option->show();
    });
    //设置选人界面
    connect(ui->menu, &MyMenu::chooseperson, [=](){
        //随机生成三个武将，两个备选，一个是对面的
        QString p[5];
        p[0] = "GuoShen";
        p[1] = "YuWenkai";
        p[2] = "YinShaofeng";
        p[3] = "QinYiming";
        p[4] = "LuoTian";
        srand(time(0));
        int a = rand()%5;
        int b = rand()%5;
        while(a == b) b = rand()%5;
        int c = rand()%5;
        while(c == b || c == a) c = rand()%5;
        //创建choose界面
        choose = new ChooseMenu(p[a],p[b]);
        //将choose界面添加到ui里
        ui->stackedWidget->addWidget(choose);
        //切换到choose界面
        ui->stackedWidget->setCurrentIndex(1);
        //选人信号发出后进入游戏，注意这里删去了难度选择，因为没用
        connect(choose,&ChooseMenu::choosehero1,[=](){
            //创建游戏界面
            //bgm->stop();
            game = new playscene(p[a], p[c]);
            ui->stackedWidget->addWidget(game);
            ui->stackedWidget->setCurrentIndex(2);
            //如果游戏结束（发出mainmenu信号），则退回到开始界面
            connect(game, &playscene::mywin, [=](){
                endsc = new endscene(0);
                ui->menu->bgm->stop();
                ui->stackedWidget->addWidget(endsc);
                ui->stackedWidget->setCurrentIndex(3);
                connect(endsc, &endscene::mainmenu, [=](){
                    ui->stackedWidget->setCurrentIndex(0);
                    ui->menu->bgm->play();
                    delete ui->stackedWidget->widget(3);
                    delete ui->stackedWidget->widget(2);
                    delete ui->stackedWidget->widget(1);
                });
            });
            connect(game, &playscene::enemywin, [=](){
                endsc = new endscene(1);
                ui->menu->bgm->stop();
                ui->stackedWidget->addWidget(endsc);
                ui->stackedWidget->setCurrentIndex(3);
                connect(endsc, &endscene::mainmenu, [=](){
                    ui->stackedWidget->setCurrentIndex(0);
                    ui->menu->bgm->play();
                    delete ui->stackedWidget->widget(3);
                    delete ui->stackedWidget->widget(2);
                    delete ui->stackedWidget->widget(1);
                });
            });
            //发出游戏开始信号
            emit game->mygamestart();
        });
        connect(choose,&ChooseMenu::choosehero2,[=](){
            //bgm->stop();
            game = new playscene(p[b], p[c]);
            ui->stackedWidget->addWidget(game);
            ui->stackedWidget->setCurrentIndex(2);
            connect(game, &playscene::mywin, [=](){
                endsc = new endscene(0);
                ui->menu->bgm->stop();
                ui->stackedWidget->addWidget(endsc);
                ui->stackedWidget->setCurrentIndex(3);
                connect(endsc, &endscene::mainmenu, [=](){
                    ui->stackedWidget->setCurrentIndex(0);
                    ui->menu->bgm->play();
                    delete ui->stackedWidget->widget(3);
                    delete ui->stackedWidget->widget(2);
                    delete ui->stackedWidget->widget(1);
                });
            });
            connect(game, &playscene::enemywin, [=](){
                endsc = new endscene(1);
                ui->menu->bgm->stop();
                ui->stackedWidget->addWidget(endsc);
                ui->stackedWidget->setCurrentIndex(3);
                connect(endsc, &endscene::mainmenu, [=](){
                    ui->stackedWidget->setCurrentIndex(0);
                    ui->menu->bgm->play();
                    delete ui->stackedWidget->widget(3);
                    delete ui->stackedWidget->widget(2);
                    delete ui->stackedWidget->widget(1);
                });
            });
            emit game->mygamestart();
        });
    });
}

MainWindow::~MainWindow(){
    delete ui;
}

