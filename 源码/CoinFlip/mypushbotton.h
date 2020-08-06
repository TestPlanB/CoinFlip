#ifndef MYPUSHBOTTON_H
#define MYPUSHBOTTON_H

#include <QWidget>
#include<QPushButton>
class MyPushBotton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushBotton(QWidget *parent = 0);
    //构造函数 参数1正常显示图片 参数2按下后显示的图片
    MyPushBotton(QString normalImg,QString pressImg="");
    //成员属性
    QString normalImgPath;
    QString pressImgPath;
    //弹跳特效
    void zoom1();
    void zoom2();

    //重写按钮 按下和释放
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    bool lock=false;


signals:

public slots:
};

#endif // MYPUSHBOTTON_H
