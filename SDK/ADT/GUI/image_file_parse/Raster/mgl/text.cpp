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
#include "CCDictionary.h"

/*
 *点阵字体
 *http://www.388g.com/dianzhen/
 */

class PFont : public CCObject{
public:
    int width;
    int height;
    char c[4];
    char *data;
};

CCDictionary dict;/*字体库*/

void drawText(const char *str, int x, int y){
    int posX = x;
    int posY = y;
    
    for(int i=0; i<strlen(str); ){
        char c[4] = {0};
        if ((unsigned char)str[i] > 128) {/*汉字*/
            memcpy(c, str+i, 3);
            i += 3;
        }
        else if ((unsigned char)str[i] <= 128){/*原ascii*/
            memcpy(c, str+i, 1);
            i += 1;
        }

        PFont *fnt = (PFont *)dict.objectForKey(c);
        for (int i=0; i<fnt->height; i++) {
            for (int j=0; j<fnt->width; j++) {
                if (fnt->data[i*fnt->width+j] == '1') {
                    mglDrawPixel(posX+j, posY+i);
                }
            }
        }
        posX += fnt->width;
    }
}

void parseFontFile(char *filename){
    MutableData d;
    d.readFile(filename);
    
    while (!d.isFinsh()) {
        PFont *fnt = new PFont;
        fnt->data = new char[1000];
        memset(fnt->data, 0, 1000);//bzero
        memset(fnt->c, 0, 4);
        fnt->width = 1;
        fnt->height = 1;
        
        d.skip(1);//skip <
//        d.parseChars(fnt->c, 3);//读汉字
        unsigned char chr;
        d.parseChar((char*)&chr);
        if (chr > 128) {/*utf-8汉字3个字节*/
            d.skip(-1);
            d.parseChars(fnt->c, 3);
        }
        else if (chr <= 128){/*utf-8原ascii1个字节*/
            d.skip(-1);
            d.parseChars(fnt->c, 1);
        }

        d.skip(3);//skip > and \r\n

        int i=0;
        char cc;
        d.parseChar(&cc);
        int flag =  true;

        while (cc != '<') {
            if (cc != '\n' && cc!= '\r') {
                fnt->data[i++] = cc;
            }
            else{
                flag = false;//遇到‘\n’后宽统计结束
                fnt->height++;//遇到‘\n’高加一
            }
            
            if (flag) {
                fnt->width++;
            }
            
            d.parseChar(&cc);
        }
        
        d.skip(3);// skip />\n
        
        dict.setObject(fnt, fnt->c);
    }
}

/*支持绘制a-z26个字母*/



