#include "mycoin.h"
#include<QDebug>
MyCoin::MyCoin(QString btnImg){
    QPixmap pix;
    bool ret=pix.load(btnImg);
    if(!ret){
        qDebug()<<"图片加载失败";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    //初始化定时器对象
    timer1=new QTimer(this);
    timer2=new QTimer(this);
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1").arg(this->min++);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //判断如果翻完了，重置min为1
        if(this->min>this->max){
            isAnimation=false;
            this->min=1;
            timer1->stop();
        }
    });
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1").arg(this->max--);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //判断如果翻完了，重置min为1
        if(this->max<this->min){
            isAnimation=false;
            this->max=8;
            timer2->stop();
        }
    });

}
 void  MyCoin::mousePressEvent(QMouseEvent *e){
     if(this->isAnimation||this->isWin){
         return;
     }
     else{
         return QPushButton::mousePressEvent(e);
     }

 }

void MyCoin::changeFlag(){
    //如果是正面
    if(this->flag){
        timer1->start(30);//30ms触发一次
        isAnimation=true;
        flag=false;
    }
    else{
        timer2->start(30);
        isAnimation=true;
        flag=true;
    }
}
