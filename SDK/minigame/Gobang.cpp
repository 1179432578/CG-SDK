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

static int p1[12][12];/*玩家一棋子布局*/
static int p2[12][12];/*玩家二棋子布局*/

/*游戏渲染*/
void gameRender(){
    drawCheckerboard(600);
    
    parseFontFile("resource/fnt.text");
    drawText("111", 700, 100);
    
    mglDisplay();
}

void initGame(){
    //指定显示回调
    glutDisplayFunc(gameRender);
    
    //指定鼠标回调
    glutMouseFunc(mouse);
    
    //指定键盘回调
    glutKeyboardFunc(keyboard);
    
    /*初始化游戏数据*/
    memset(p1, 0, sizeof(p1));
    memset(p2, 0, sizeof(p2));
}

/*画棋盘*/
void drawCheckerboard(int size){
    mglSetColor(0, 0.5, 0.5, 0);
    for (int i=0; i<=size; i+=50) {
        mglMoveTo(0, i);
        mglLineTo(size-1, i);
        
        mglMoveTo(i, 0);
        mglLineTo(i, size-1);
    }
}

/*画棋子*/
void drawPiece(int x, int y){
    mglSetColor(0, 0, 1, 1);
    mglDrawCircle(x, y, 20);
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
            /*调整坐标x,y做到棋盘交点上*/
            int cellX = roundf(x / 50.0f);
            int cellY = roundf(y / 50.0f);
            if (cellX >= 1 && cellX <= 11 && cellY >= 1 && cellY <= 11) {
                drawPiece(cellX * 50, cellY * 50);
                p1[cellY][cellX] = true;
                glutPostRedisplay();
                
                if (checkWin(p1, cellX, cellY)) {
                    printf("You Win!\n");
                }
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