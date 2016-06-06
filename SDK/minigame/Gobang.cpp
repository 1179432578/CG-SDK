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

//static int p1[12][12];/*玩家一棋子布局*/
//static int p2[12][12];/*玩家二棋子布局*/
static bool bNext = true;/*双方一开始都可以先走棋，走一步后，等对方走棋*/

static Piece *p1;
static Piece *p2;
static PointFont *text1;
static PointFont *text2;

void gameRender(){
}

void initGame(){
    /*set mgl*/
    
    //指定显示回调
    glutDisplayFunc(gameRender);
    
    //指定鼠标回调
    glutMouseFunc(mouse);
    
    //指定键盘回调
    glutKeyboardFunc(keyboard);
    
    registerMainLoop();
    
    /*加载字体库*/
    parseFontFile("resource/fnt.text");
    
    /*初始化场景*/
    p1 = new Piece;
    p1->setColor(Color(0,0,0));
    Manager::getInstance()->addNode(p1);
    p2 = new Piece;
    p2->setColor(Color(1,0,0));
    Manager::getInstance()->addNode(p2);
    
    CheckerBoard *borad = new CheckerBoard;
    Manager::getInstance()->addNode(borad);
    
    /*text1*/
    text1 = PointFont::create("", 600, 0);
    Manager::getInstance()->addNode(text1);
    text2 = PointFont::create("", 600, 200);
    Manager::getInstance()->addNode(text2);
    
    /*与服务器建立连接*/
    connectServer();
}

void drawOtherPiece(int x, int y){
    p2->setXY(x, y);
    
    /*检查对方是否胜利*/
    if (p2->checkWin(x, y)) {
        text2->setText("你输了");
    }
    
    bNext = true;/*下一步走棋*/
}

void mouse(int button, int state, int x, int y){
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            if (!bNext) {/*不能走棋,返回不做任何操作*/
                return;
            }
            
            /*走棋*/
            int cellX = roundf(x / 50.0f);
            int cellY = roundf(y / 50.0f);
            if (cellX >= 1 && cellX <= 11 && cellY >= 1 && cellY <= 11) {
                if(p1->getXY(cellX, cellY)|| p2->getXY(cellX, cellY)){/*不准覆盖原来棋盘上棋子*/
                    return;
                }
                
                p1->setXY(cellX, cellY);
                
                /*发送消息给服务器*/
                char msg[8];
                memcpy(msg, &cellX, 4);
                memcpy(msg+4, &cellY, 4);
                sendMsg(msg, 8);
                
                /*检查是否胜利*/
                if (p1->checkWin(cellX, cellY)) {
                    text2->setText("你赢了");
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
    }
}
