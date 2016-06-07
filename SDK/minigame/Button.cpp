//
//  Button.cpp
//  CG
//
//  Created by 鲁飞 on 16/6/7.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "Button.h"
#include <string.h>
#include "mgl.h"
#include "text.h"

Button* Button::create(int x, int y, int width, int height, char *text){
    Button *ret = new Button;
    ret->m_posX = x;
    ret->m_posY = y;
    int size = strlen(text) + 1;
    ret->m_text = new char[size];
    memcpy(ret->m_text, text, size);
    ret->m_width = width;
    ret->m_height = height;
    
    return ret;
}

void Button::draw(){
    mglColor(1, 0.3, 0.3, 1);
    mglDrawRectangle(m_posX, m_posY, m_width, m_height);
    mglColor(0, 0, 0, 1);
    drawText(m_text, m_posX, m_posY);
}
