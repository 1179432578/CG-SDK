//
//  Gobang.cpp
//  CG
//
//  Created by lewis on 16/6/5.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "Gobang.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "text.h"
#include "server.h"
#include "Node.h"
#include "MainLoop.h"
#include <math.h>
#include "TouchDispatcher.h"
#include "control.h"
#include "Texture2D.h"

//static int p1[12][12];/*玩家一棋子布局*/
//static int p2[12][12];/*玩家二棋子布局*/
static bool bNext = true;/*双方一开始都可以先走棋，走一步后，等对方走棋*/

static Piece *p1;
static Piece *p2;
static PointFont *text1;
static PointFont *text2;
static PointFont *text3;/*谁走棋*/
static PointFont *text4_1;/*每步倒计时*/
static PointFont *text4_2;
static PointFont *text5;/*游戏时间*/
static PointFont *text6;/*第几手*/
static DrawNode *indicate;
static Button *btn;

static int currentPlayer;/*当前谁走棋1自己2对方*/
static bool gameState;/*游戏状态：开始、结束*/
static float timeLeft;/*倒计时*/

void gameRender(){
}

void initGame(){
    /*init data*/
    gameState = true;
    currentPlayer = 1;
    timeLeft = 60;
    
    //指定显示回调
    glutDisplayFunc(gameRender);
    
    //指定鼠标回调
    glutMouseFunc(mouse);
    
    //指定键盘回调
    glutKeyboardFunc(keyboard);
    
    registerMainLoop();
    
    /*加载字体库*/
    parseFontFile("fnt.text");
    
    /*初始化场景*/
    /*test*/
    Texture2D *tex = Texture2D::create(200, 200,  "Icon-72@2x.png");
    Manager::getInstance()->addNode(tex);

    
    
    indicate = DrawNode::create(100-25, 100-25);
    indicate->setVisible(false);
    Manager::getInstance()->addNode(indicate);
    
    p1 = new Piece;
    p1->setColor(Color(0,0,0));
    p1->setPosition(50, 50);
    Manager::getInstance()->addNode(p1);
    p2 = new Piece;
    p2->setColor(Color(1,1,1));
    p2->setPosition(50, 50);
    Manager::getInstance()->addNode(p2);
    
    CheckerBoard *borad = new CheckerBoard;
    TouchDispatcher::getInstance()->addDelegate(borad);
    borad->setPosition(50, 50);
    Manager::getInstance()->addNode(borad);
    
    /*text1*/
    text1 = PointFont::create("", 600, 0);
    Manager::getInstance()->addNode(text1);
    text2 = PointFont::create("", 400, 0);
    Manager::getInstance()->addNode(text2);
    text3 = PointFont::create("请走棋", 100, 0);
    Manager::getInstance()->addNode(text3);
    text4_1 = PointFont::create("倒计时:", 200, 0);
    Manager::getInstance()->addNode(text4_1);
    text4_2 = PointFont::create("60:00",270, 0);
    Manager::getInstance()->addNode(text4_2);
    text4_2->setVisible(true);
    
    Scene *s = new Scene;
    Button *button = Button::create(0, 0, 200, 100, s, event_selector(Scene::click));
    TouchDispatcher::getInstance()->addDelegate(button);
    Manager::getInstance()->addNode(button);
    
    /*与服务器建立连接*/
    connectServer();
}

void drawOtherPiece(int x, int y){
    p2->setXY(x, y);
    text3->setText("请走棋");
    text4_2->setText("60:00");
    text4_2->setVisible(true);
    currentPlayer = 1;
    timeLeft = 60;
    
    /*检查对方是否胜利*/
    if (p2->checkWin(x, y)) {
        text2->setText("你输了");
        text3->setVisible(false);
        gameState = false;
        text4_1->setVisible(false);
        text4_2->setVisible(false);
    }
    
    bNext = true;/*下一步走棋*/
}

void mouse(int button, int state, int x, int y){
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            /*touch dispatcher*/
            static Touch *pTouch = new Touch();
            pTouch->setTouchInfo(x, y);
            TouchDispatcher::getInstance()->touch(pTouch, NULL, TOUCHBEGAN);
            
            if (!bNext || !gameState) {/*不能走棋,返回不做任何操作*/
                return;
            }
            
            /*走棋*/
            int cellX = roundf(x / 50.0f) - 1;
            int cellY = roundf(y / 50.0f) - 1;
            if (cellX >= 0 && cellX <= 14 && cellY >= 0 && cellY <= 14) {
                if(p1->getXY(cellX, cellY)|| p2->getXY(cellX, cellY)){/*不准覆盖原来棋盘上棋子*/
                    return;
                }
                
                p1->setXY(cellX, cellY);
                currentPlayer = 2;
                indicate->setVisible(true);
                indicate->setPosition(cellX*50+50-25, cellY*50+50-25);
                text3->setText("对方走棋");
                timeLeft = 60;
                
                /*发送消息给服务器*/
                char msg[8];
                memcpy(msg, &cellX, 4);
                memcpy(msg+4, &cellY, 4);
                sendMsg(msg, 8);
                
                /*检查是否胜利*/
                if (p1->checkWin(cellX, cellY)) {
                    text2->setText("你赢了");
                    text3->setVisible(false);
                    gameState = false;
                    text4_1->setVisible(false);
                    text4_2->setVisible(false);
                }
                
                bNext = false;/*下一步对方走棋*/
            }
            
        }
    }
    
}

void keyboard(unsigned char keyValue, int x, int y){
    switch (keyValue) {
        case 'q':
            printf("EXIT\n");
            exit(-1);
            break;
            
        default:
            break;
    }
}

void handleRev(char *buf){
    if (strcmp(buf, "OK") == 0) {
        text1->setText("与服务器建立连接");
    }
    else{
        int cellX, cellY;
        memcpy(&cellX, buf, 4);
        memcpy(&cellY, buf+4, 4);
        //printf("接收到对战玩家数据%d %d\n", cellX, cellY);
        
        /*把对战玩家棋子画出来*/
        drawOtherPiece(cellX, cellY);
        indicate->setVisible(true);
        indicate->setPosition(cellX*50+50-25, cellY*50+50-25);
    }
}

void logicHandle(float delta){
    if (gameState) {/*游戏开始了*/
        timeLeft -= delta;/*mn:pq*/
        
        if (timeLeft < 0.0f) {
            if (currentPlayer == 1) {/*本方走棋*/
                gameState = false;
                text2->setText("你输了");
            }
            else if (currentPlayer == 2){/*对方走棋*/
                 gameState = false;
                text2->setText("你赢了");
            }
        }
        int m = floorf(timeLeft / 10);
        int n = timeLeft - m * 10;
        char s[3] = {0};
        s[0] = m + '0';
        s[1] = n + '0';
        text4_2->setText(s);
    }
}
