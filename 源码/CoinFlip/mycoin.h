#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = 0);
    //传入的金币或银币路径
    MyCoin(QString btnImg);

    //属性
    int posX;
    int posY;
    bool flag;//正反状态

    //改变标志方法
    void changeFlag();
    QTimer *timer1;//正->反
    QTimer *timer2;
    int min=1;
    int max=8;
    //执行动画标志
    bool isAnimation=false;
    //重写按下
    void mousePressEvent(QMouseEvent *e);
    //是否胜利
    bool isWin=false;//若无初始值则随机指定，因此会出现银币翻不动

signals:
    void timeOut();

public slots:
};

#endif // MYCOIN_H
