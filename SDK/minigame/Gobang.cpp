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

static int p1[12][12];/*玩家一棋子布局*/
static int p2[12][12];/*玩家二棋子布局*/
static bool bRun = true;/*双方一开始都可以先走棋，走一步后，等对方走棋*/

/*游戏渲染*/
void gameRender(){
    drawCheckerboard(600);
    
    mglSetColor(0, 0.3, 0.7, 1);
    
    mglDisplay();
}

void initGame(){
    /*set mgl*/
    mglClearColor(1, 1, 1, 1);
    mglClear(MGL_COLOR_BUFFER_BIT);
    
    //指定显示回调
    glutDisplayFunc(gameRender);
    
    //指定鼠标回调
    glutMouseFunc(mouse);
    
    //指定键盘回调
    glutKeyboardFunc(keyboard);
    
    /*初始化游戏数据*/
    memset(p1, 0, sizeof(p1));
    memset(p2, 0, sizeof(p2));
    
    /*加载字体库*/
    parseFontFile("resource/fnt.text");
    
    /*与服务器建立连接*/
    connectServer();
}

/*画棋盘*/
void drawCheckerboard(int size){
    mglSetColor(0, 0, 0, 0);
    for (int i=0; i<=size; i+=50) {
        mglMoveTo(0, i);
        mglLineTo(size-1, i);
        
        mglMoveTo(i, 0);
        mglLineTo(i, size-1);
    }
}

/*画棋子*/
void drawPiece(int x, int y){
    mglDrawCircle(x, y, 20);
    mglFillCircle(x, y, 20);
    glutPostRedisplay();
}

void drawOtherPiece(int x, int y){
    mglSetColor(1, 0, 0, 1);
    drawPiece(x * 50, y * 50);
    p2[y][x] = true;
    
    /*检查对方是否胜利*/
    if (checkWin(p2, x, y)) {
       drawText("你输了", 700, 100);
        printf("You Lose!\n");
    }
    
    bRun = true;/*下一步走棋*/
}

bool checkWin(int arr[][12], int x, int y){
    /*进行左右检查*/
    int num = 1;
    int i = x - 1;
    int j;
    while (arr[y][i]) {
        num++;
        i--;
    }
    i = x + 1;
    while (arr[y][i]) {
        num++;
        i++;
    }
    if (num >=5) {
        return true;
    }
    
    //进行上下检查
    num = 1;
    i = y + 1;
    while(arr[i][x]){
        num++;
        i++;
    }
    i = y - 1;
    while(arr[i][x]){
        num++;
        i--;
    }
    if (num >= 5) {
        return true;
    }
    
    //进行左上检查
    num = 1;
    i = x - 1;
    j = y - 1;
    while(arr[j][i]){
        num++;
        i--;
        j--;
    }
    i = x + 1;
    j = y + 1;
    while(arr[j][i]){
        num++;
        i++;
        j++;
    }
    if (num >= 5) {
        return true;
    }
    
    //进行右上检查
    num = 1;
    i = x + 1;
    j = y - 1;
    while(arr[j][i]){
        num++;
        i++;
        j--;
    }
    i = x - 1;
    j = y + 1;
    while(arr[j][i]){
        num++;
        i--;
        j++;
    }
    if (num >= 5) {
        return true;
    }

    return false;
}

void mouse(int button, int state, int x, int y){
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            if (!bRun) {/*不能走棋*/
                return;
            }
            
            /*走棋*/
            int cellX = roundf(x / 50.0f);
            int cellY = roundf(y / 50.0f);
            if (cellX >= 1 && cellX <= 11 && cellY >= 1 && cellY <= 11) {
                if(p1[cellY][cellX] || p2[cellY][cellX]){/*不准覆盖原来棋盘上棋子*/
                    return;
                }
                mglSetColor(0, 0, 1, 1);
                drawPiece(cellX * 50, cellY * 50);
                p1[cellY][cellX] = true;
                
                /*发送消息给服务器*/
                char msg[8];
                memcpy(msg, &cellX, 4);
                memcpy(msg+4, &cellY, 4);
                sendMsg(msg, 8);
                
                /*检查是否胜利*/
                if (checkWin(p1, cellX, cellY)) {
                    drawText("你赢了", 700, 100);
                    printf("You Win!\n");
                }
                
                bRun = false;/*下一步对方走棋*/
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
