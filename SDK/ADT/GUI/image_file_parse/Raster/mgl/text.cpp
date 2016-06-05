//
//  text.cpp
//  CG
//
//  Created by lewis on 16/6/5.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "text.h"
#include "mgl.h"
#include "MutableData.h"

/*
 *点阵字体
 *http://www.388g.com/dianzhen/
 */

char *fnt;/*字体库*/
int width;
int height;

char *yin = "0000000000000000000000\
0000000000000000000000\
0000000000000000000000\
0000000001110000000000\
0111111111111111111110\
0111111111111111111110\
0001110000000000000000\
0001111111111111110000\
0000000000000000000000\
0001111111111111111000\
0001110000000001111000\
0001110000000001111000\
0001111111111111111000\
0000000000000000000000\
0111111111111111111100\
0111011111011111011100\
0111111111111111111100\
0111011111111111111100\
0111011111111111111100\
0111111111110111111100\
0111011111111111011110\
0111111111111111011111\
0111111111001110001110\
0000000000000000000000\
0000000000000000000000";

void drawText(const char *str, int x, int y){
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            if (fnt[i*width+j] == '1') {
                mglDrawPixel(x+j, y+i);
            }
        }
    }
}

void parseFontFile(char *filename){
    MutableData d;
    d.readFile(filename);
    
    d.skip(1);//<
    short c = d.parseShort();//读汉字
    d.skip(3);//跳过>与换行符
    
    fnt = new char[1000];//足够大
    memset(fnt, 0, 1000);
    int i=0;
    char cc;
    d.parseChar(&cc);
    int flag =  true;
    width = 0;
    height = 0;
    while (cc != '<') {
        if (cc != '\n' && cc!= '\r') {
            fnt[i++] = cc;
        }
        else{
            flag = false;//遇到‘\n’后宽统计结束
            height++;//遇到‘\n’高加一
        }
        
        if (flag) {
            width++;
        }
        
        d.parseChar(&cc);
    }
    
    int a =5;
}

/*支持绘制a-z26个字母*/



