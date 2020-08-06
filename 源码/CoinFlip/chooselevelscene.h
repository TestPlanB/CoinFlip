#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include"playscene.h"
#include"mypushbotton.h"
#include<QLabel>
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = 0);
    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //游戏场景对象指针
    PlayScene *play=NULL;
    MyPushBotton *lockBtn[20];
    QLabel *labelLock[20];


signals:
    //写一个自定义信号 返回主场景
    void chooseSceneBack();



public slots:
};

#endif // CHOOSELEVELSCENE_H
