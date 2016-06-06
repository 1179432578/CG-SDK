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

void CheckerBoard::draw(){
    mglSetColor(0, 0, 0, 0);/*黑色线条*/
    int size = 600;
    for (int i=0; i<=size; i+=50) {
        mglMoveTo(0, i);
        mglLineTo(size-1, i);
        
        mglMoveTo(i, 0);
        mglLineTo(i, size-1);
    }
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
        p->draw();
        p = p->m_next;
    }
    
    mglDisplay();
}

void Piece::draw(){
    mglSetColor(m_color.r, m_color.g, m_color.b, 1);
    for (int i=1; i<12; i++) {
        for (int j=1; j<12; j++) {
            if (m_piece[j][i]) {
                mglFillCircle(i*50, j*50, 20);
            }
            
        }
    }
}

void Piece::setXY(int x, int y){
    if (x >= 12 || x < 0 || y >= 12 || y < 0) {
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
    mglColor(0, 0, 1, 1);
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