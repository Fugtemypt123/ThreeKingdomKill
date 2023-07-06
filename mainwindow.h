#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QApplication>
#include "choosemenu.h"
#include "playscene.h"
#include "endscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//这是游戏窗口的类
class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent=nullptr);
    ~MainWindow();
    ChooseMenu *choose; //选人界面是开始界面的成员
    playscene *game; //游戏界面是开始界面的成员
    endscene *endsc;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
