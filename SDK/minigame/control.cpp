//
//  control.cpp
//  CG
//
//  Created by lewis on 16/6/10.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "control.h"
#include "mgl.h"

Button* Button::create(int x, int y, int width, int height, Object *target, SEL_EventHandler selector){
    Button *ret = new Button;
    ret->m_posX = x;
    ret->m_posY = y;
    ret->m_width = width;
    ret->m_height = height;
    ret->m_selector = selector;
    ret->m_target = target;
    
    return ret;
}

bool Button::touchBegan(Touch *pTouch, Event *pEvent){
    TiPoint p = pTouch->getLocationInView();
    
    if (p.x > m_posX && p.x < m_posX + m_width && p.y > m_posY && p.y < m_posY + m_height) {
        if (m_selector) {
            (m_target->*m_selector)(pEvent);/*调用目标动作*/
        }
    }
    
    return false;
}

void Button::draw(){
    mglSetColor(0.4, 0.3, 0.7, 1);
    mglDrawRectangle(m_posX, m_posY, m_width, m_height);
}