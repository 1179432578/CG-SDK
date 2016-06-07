//
//  Node.cpp
//  CG
//
//  Created by lewis on 16/6/6.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "Node.h"
#include "mgl.h"
#include <string.h>
#include "text.h"

Node *m_head = NULL;//bug

void Node::setPosition(int x, int y){
    m_posX = x;
    m_posY = y;
}

void CheckerBoard::draw(){
    /*画底盘*/
    mglSetColor(244.0f/255, 146.0f/255, 111.0f/255, 0);
    mglDrawRectangle(m_posX, m_posY, 700, 700);
    
    mglSetColor(0, 0, 0, 0);/*黑色线条*/
    int size = 700;
    for (int i=0; i<=size; i+=50) {
        mglMoveTo(m_posX+0,m_posY+i);
        mglLineTo(m_posX+size-1, m_posY+i);
        
        mglMoveTo(m_posX+i, m_posY+0);
        mglLineTo(m_posX+i, m_posY+size-1);
    }
    
    /*画五个点*/
    mglSetColor(0, 0, 0, 0);
    mglFillCircle(m_posX+3*50, m_posY+3*50, 5);
    mglFillCircle(m_posX+11*50, m_posY+3*50, 5);
    mglFillCircle(m_posX+7*50, m_posY+7*50, 5);
    mglFillCircle(m_posX+3*50, m_posY+11*50, 5);
    mglFillCircle(m_posX+11*50, m_posY+11*50, 5);
}

static Manager *ret = NULL;
Manager* Manager::getInstance(){
    if (!ret) {
        ret = new Manager;
//        ret->m_head = NULL;
        return ret;
    }
    
    return NULL;
}

void Manager::addNode(Node *p){
    /*插到头部*/
    p->m_next = m_head;
    m_head = p;
}

void Manager::removeNode(Node *p){
    Node *m = m_head;
    Node *pre = NULL;
    while (m) {
        if (m == p) {
            if (pre) {
                pre->m_next = p->m_next;
                delete p;
            }
            else{
                m_head = p->m_next;
                delete p;
            }
            
            break;
        }
        
        pre = m;
        m = m->m_next;
    }
}

void Manager::drawScene(){
    mglClearColor(1, 1, 1, 1);
    mglClear(MGL_COLOR_BUFFER_BIT);
    
    Node *p = m_head;
    while (p) {
        if (p->m_visible) {
            p->draw();
        }
        p = p->m_next;
    }
    
    mglDisplay();
}

void Piece::draw(){
    mglSetColor(m_color.r, m_color.g, m_color.b, 1);
    for (int i=0; i<15; i++) {
        for (int j=0; j<15; j++) {
            if (m_piece[j][i]) {
                mglFillCircle(m_posX+i*50, m_posY+j*50, 20);
            }
            
        }
    }
}

void Piece::setXY(int x, int y){
    if (x > 14 || x < 0 || y > 14 || y < 0) {
        return;
    }
    
    m_piece[y][x] = true;
}

bool Piece::getXY(int x, int y){
    return m_piece[y][x];
}

bool Piece::checkWin(int x, int y){
    /*进行左右检查*/
    int num = 1;
    int i = x - 1;
    int j;
    while (m_piece[y][i]) {
        num++;
        i--;
    }
    i = x + 1;
    while (m_piece[y][i]) {
        num++;
        i++;
    }
    if (num >=5) {
        return true;
    }
    
    //进行上下检查
    num = 1;
    i = y + 1;
    while(m_piece[i][x]){
        num++;
        i++;
    }
    i = y - 1;
    while(m_piece[i][x]){
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
    while(m_piece[j][i]){
        num++;
        i--;
        j--;
    }
    i = x + 1;
    j = y + 1;
    while(m_piece[j][i]){
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
    while(m_piece[j][i]){
        num++;
        i++;
        j--;
    }
    i = x - 1;
    j = y + 1;
    while(m_piece[j][i]){
        num++;
        i--;
        j++;
    }
    if (num >= 5) {
        return true;
    }
    
    return false;
}

void Piece::setColor(Color color){
    m_color = color;
}

PointFont* PointFont::create(char *text, int x, int y){
    PointFont *ret = new PointFont;
    ret->setText(text);
    ret->m_posX = x;
    ret->m_posY = y;
    
    return ret;
}

void PointFont::draw(){
    mglColor(77.0f/255, 39.0f/255, 25.0f/255, 1);
    drawText(m_text, m_posX, m_posY);
}

void PointFont::setText(char *text){
    if (m_text) {
        delete [] m_text;
    }
    int n = strlen(text) + 1;
    m_text = new char[n];
    memcpy(m_text, text, n);
}

DrawNode* DrawNode::create(int x, int y){
    DrawNode *ret = new DrawNode;
    ret->m_posX = x;
    ret->m_posY = y;
    
    return ret;
}

void DrawNode::draw(){
    mglColor(1, 0, 0, 1);
    mglMoveTo(m_posX, m_posY);
    mglLineTo(m_posX, m_posY+22);
    mglMoveTo(m_posX, m_posY);
    mglLineTo(m_posX+22, m_posY);
    
    mglMoveTo(m_posX, m_posY+50);
    mglLineTo(m_posX, m_posY+50-22);
    mglMoveTo(m_posX, m_posY+50);
    mglLineTo(m_posX+22, m_posY+50);
    
    mglMoveTo(m_posX+50, m_posY);
    mglLineTo(m_posX+50-22, m_posY);
    mglMoveTo(m_posX+50, m_posY);
    mglLineTo(m_posX+50, m_posY+22);
    
    mglMoveTo(m_posX+50, m_posY+50);
    mglLineTo(m_posX+50-22, m_posY+50);
    mglMoveTo(m_posX+50, m_posY+50);
    mglLineTo(m_posX+50, m_posY+50-22);
    
    mglMoveTo(m_posX+13, m_posY+25);
    mglLineTo(m_posX+13+24, m_posY+25);
    mglMoveTo(m_posX+25, m_posY+13);
    mglLineTo(m_posX+25, m_posY+13+24);
}