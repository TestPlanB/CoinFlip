#include "playscene.h"
#include<QMenuBar>
#include<QPainter>
#include"mypushbotton.h"
#include<QTimer>
#include<QLabel>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QRect>
#include<QSound>
#include<QDialog>
#include<QMessageBox>
PlayScene::PlayScene(int levelNum){
    this->levelIndex=levelNum;


    //初始化游戏场景
    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("翻金币场景");
    QMenuBar *bar=menuBar();
    setMenuBar(bar);
    QMenu *startMenu=bar->addMenu("开始");

    //创建退出菜单项
    QAction *quitAction =startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //返回按钮
    MyPushBotton *backBtn=new MyPushBotton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());


    //音效资源
    //音效
    QSound  *flipSound=new QSound(":/res/ConFlipSound.wav",this);
    QSound  *winSound=new QSound(":/res/LevelWinSound.wav",this);
    QSound  *backSound=new QSound(":/res/BackButtonSound.wav",this);

    //点击返回
    connect(backBtn,&MyPushBotton::clicked,[=]{
        backSound->play();
        //告诉场景 返回 场景要监听Chooselevelscene的返回按钮
        QTimer::singleShot(500,this,[=](){
             emit this->chooseSceneBack();//emit 发送信号
        });
    });

    //显示当前关卡
    QLabel *label=new QLabel;

    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    //字体设置到标签中
    label->setFont(font);
    QString str=QString("Level:%1").arg(this->levelIndex);
    label->setText(str);
    label->setGeometry(30,this->height()-50,120,50);//大小位置并显示
    label->setParent(this);

    //初始化关卡
    dataConfig config;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }
    //胜利图片显示
    QLabel *winLabel=new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());//-tempPix 是放在屏幕上面






   // 列出倒计时label QPalette指定调色板 Qtimer要new出来才能正常使用
    QLabel *timeLoc=new QLabel;
    timeLoc->setParent(this);
    timeLoc->setFont(font);
    QString str1=QString("Time:%1").arg(100);
    timeLoc->setText(str1);
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::white);
    timeLoc->setPalette(pe);
    timeLoc->setGeometry(200,70,120,50);//大小位置

    static int timeout=11;
    QTimer *timerLoc=new QTimer(this);
    timerLoc->start(1000);
    connect(timerLoc,&QTimer::timeout,[=](){

        QString strTemp;
        strTemp=QString("Time:%1").arg(--timeout);
        if(timeout<=0){
            //暂停所有按钮
            strTemp=QString("TimeOver");
            timeLoc->setText(strTemp);
            timerLoc->stop();

            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    coinBtn[i][j]->isWin=true;
                }
            }
           QMessageBox::information(this,"关卡提示","你已经输了");
           timeout=11;


        }

        timeLoc->setText(strTemp);

    });



    //创建背景图
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            //timeLoc->show();
            //绘制背景图片
            QLabel *label=new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->setParent(this);
            label->move(57+i*50,200+j*50);
            //创建金币
            QString str;
            if(this->gameArray[i][j]==1){
                //显示金币
                str=":/res/Coin0001.png";
            }
            else{
                str=":/res/Coin0008.png";
            }
            MyCoin *coin=new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            //属性赋值
            coin->posX=i;
            coin->posY=j;
            coin->flag=this->gameArray[i][j];
            //将金币放入金币的二维数组
            coinBtn[i][j]=coin;



            //点击金币翻转
            connect(coin,&MyCoin::clicked,[=](){
                //播放金币音效
                flipSound->play();
                //点击后禁用其他按钮
                for(int i=0;i<4;i++){
                    for(int j=0;j<4;j++){
                        coinBtn[i][j]->isWin=true;
                    }
                }
               coin->changeFlag();
               this->gameArray[i][j]=this->gameArray[i][j]==0?1:0;

               QTimer::singleShot(300,this,[=](){
                   //翻转周围的硬币
                   if(coin->posX+1<=3)//右侧周围翻转的条件
                   {
                       coinBtn[coin->posX+1][coin->posY]->changeFlag();
                       this->gameArray[coin->posX+1][coin->posY]=this->gameArray[coin->posX+1][coin->posY]==0?1:0;

                   }
                   //左侧翻转
                   if(coin->posX-1>=0){
                       coinBtn[coin->posX-1][coin->posY]->changeFlag();
                       this->gameArray[coin->posX-1][coin->posY]=this->gameArray[coin->posX-1][coin->posY]==0?1:0;
                   }
                   if(coin->posY+1<=3){
                       coinBtn[coin->posX][coin->posY+1]->changeFlag();
                       this->gameArray[coin->posX][coin->posY+1]=this->gameArray[coin->posX][coin->posY+1]==0?1:0;
                   }
                   if(coin->posY-1>=0){
                       coinBtn[coin->posX][coin->posY-1]->changeFlag();
                       this->gameArray[coin->posX][coin->posY-1]=this->gameArray[coin->posX][coin->posY-1]==0?1:0;
                   }
                   //bug 禁用其他按钮
                   for(int i=0;i<4;i++){
                       for(int j=0;j<4;j++){
                           coinBtn[i][j]->isWin=false;
                       }
                   }


                   //判断是否胜利
                   this->isWin=true;
                   for(int i=0;i<4;i++){
                       for(int j=0;j<4;j++){
                           if(coinBtn[i][j]->flag==false){
                               this->isWin=false;
                               break;
                           }
                       }
                   }
                   if(this->isWin){
                       winSound->play();
                       //胜利了
                       //将按钮胜利标志改为true
                       for(int i=0;i<4;i++){
                           for(int j=0;j<4;j++){
                               coinBtn[i][j]->isWin=true;
                           }
                       }
                       //暂停计时器
                        timerLoc->stop();
                        timeout=100;
                       //胜利图片下来
                       QPropertyAnimation *animation=new QPropertyAnimation(winLabel,"geometry");
                       //设置时间间隔
                       animation->setDuration(1000);
                       //设置位置-曲线
                       animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                       animation->setEndValue(QRect(winLabel->x(),winLabel->y()+144,winLabel->width(),winLabel->height()));
                       animation->setEasingCurve(QEasingCurve::OutBounce);
                       animation->start();
                   }





               });


            });

        }
    }



}
 void PlayScene::paintEvent(QPaintEvent *){
     QPainter painter(this);
     QPixmap pix;
     pix.load(":/res/PlayLevelSceneBg.png");
     painter.drawPixmap(0,0,this->width(),this->height(),pix);
     pix.load(":/res/Title.png");
     pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
     painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
 }

