#include "chooselevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include"mypushbotton.h"
#include<QTimer>
#include<QLabel>
#include<QSound>
#include<QDialog>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡场景");

    //创建菜单栏
    QMenuBar *bar=menuBar();
    setMenuBar(bar);
    QMenu *startMenu=bar->addMenu("开始");

    //创建退出菜单项
    QAction *quitAction =startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    //音效
    QSound  *chooseSound=new QSound(":/res/TapButtonSound.wav",this);
    QSound  *backSound=new QSound(":/res/BackButtonSound.wav",this);
    //返回按钮
    MyPushBotton *backBtn=new MyPushBotton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&MyPushBotton::clicked,[=]{


        //告诉主场景 返回 主场景要监听Chooselevelscene的返回按钮
        QTimer::singleShot(500,this,[=](){
             emit this->chooseSceneBack();//emit 发送信号
        });
         backSound->play();
    });
    //音效




    //创建选择关卡按钮
    for(int i=0;i<20;i++){

        MyPushBotton *menuBtn=new MyPushBotton(":/res/LevelIcon.png");

        menuBtn->lock=true;
        if(i==0){
            menuBtn->lock=false;
        }

        menuBtn->setParent(this);
        lockBtn[i]=menuBtn;
        menuBtn->move(25+i%4*70,130+i/4*70);//单层for循环画出矩阵i%4*50,i/4*50
        //初始为第一关，不锁住

        //监听每个按钮的点击事件
        connect(menuBtn,&MyPushBotton::clicked,[=](){

            //播放关卡音效
            chooseSound->play();
            //进入游戏场景

            this->hide();
            play=new PlayScene(i+1);


            play->setGeometry(this->geometry());
            play->show();

            //如果上一关胜利 解开本次锁并显示下一关序号

            connect(play,&PlayScene::chooseSceneBack,[=](){
                if(play->isWin==true){
                    if(i<20){
                        lockBtn[i+1]->lock=false;
                        labelLock[i+1]->setText(QString::number(i+2));


                }
                }
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play=NULL;

            });
        });


        QLabel *label=new QLabel;
        QFont font;
        font.setFamily("华文新魏");
        font.setPointSize(35);
        //字体设置到标签中

        label->setFixedSize(menuBtn->width(),menuBtn->height());

        label->setFont(font);

        if(menuBtn->lock==true){

            label->setText(QString("X"));
        }
        else{
        label->setText(QString::number(i+1));
        }
        label->move(25+i%4*70,130+i/4*70);
        //设置label文字对齐方式
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //设置让鼠标进行穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
        labelLock[i]=label;
        label->setParent(this);
    }


}
void ChooseLevelScene::paintEvent(QPaintEvent *){
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);

}


