#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include"mypushbotton.h"
#include"chooselevelscene.h"
#include<QTimer>
#include<QSound>  //多媒体
MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //配置主场景

    //设置固定大小
    setFixedSize(320,588);

    //设置图标

    setWindowIcon(QIcon(":/res/Coin0001.png"));

    setWindowTitle("翻金币");
    //退出按钮实现
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });
    //准备音效
    QSound  *startSound=new QSound(":/res/TapButtonSound.wav",this);
    //重复音效startSound->setLoops(-1);

    //开始按钮
    MyPushBotton *startBtn=new MyPushBotton(":/res/MenuSceneStartButton.png");

    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);
    chooseScene=new ChooseLevelScene;
     //监听选择关卡返回
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
        this->setGeometry(chooseScene->geometry());
       //重新显示主场景
        chooseScene->hide();//将选择关卡隐藏
        this->show();

    });

    connect(startBtn,&MyPushBotton::clicked,[=](){

        //做弹起特效
        startBtn->zoom1();
        startBtn->zoom2();

        startSound->play();
        //延时进入到选择关卡场景中
        QTimer::singleShot(500,this,[=](){
            chooseScene->setGeometry(this->geometry());
            //自身隐藏
            this->hide();
            chooseScene->show();


        });




    });
    startBtn->setParent(this);


}

MainScene::~MainScene()
{
    delete ui;
}
void MainScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //画背景上的图标
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);


}

