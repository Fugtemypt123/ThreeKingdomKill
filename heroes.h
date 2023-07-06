#ifndef HEROES_H
#define HEROES_H

#include <QLabel>
#include <QMovie>
#include <QSound>
#include <QTimer>
#include "cards.h"

//这是武将类
class Heroes : public QLabel{
    Q_OBJECT
public:
    Heroes(QString name, int np, bool player, QWidget *parent=0); //构造函数
    QString name; //武将的名字，加载图像时也有用
    QPixmap picture; //武将的图像
    QLabel *hppic[6]; //生命值图像，这是一张图片重复多次的形式
    bool armedak;
    int hp; //当前血量
    int totalhp; //血量上限
    bool haveweapon = false; //是否装备了武器，目前没用
    void sethp(int nowhp); //将hp设置成nowhp
    void armak();

signals:

public slots:
};

//郭神
class GuoShen : public Heroes{
    Q_OBJECT
public:
    GuoShen(bool player, QWidget *parent=0);

signals:

public slots:
};

//余文凯
class YuWenkai : public Heroes{
    Q_OBJECT
public:
    YuWenkai(bool player, QWidget *parent=0);

signals:

public slots:
};

//殷绍峰
class YinShaofeng : public Heroes{
    Q_OBJECT
public:
    YinShaofeng(bool player, QWidget *parent=0);

signals:

public slots:
};

//秦艺铭
class QinYiming : public Heroes{
    Q_OBJECT
public:
    QinYiming(bool player, QWidget *parent=0);

signals:

public slots:
};

//罗天
class LuoTian : public Heroes{
    Q_OBJECT
public:
    LuoTian(bool player, QWidget *parent=0);

signals:

public slots:
};

#endif // HEROES_H
