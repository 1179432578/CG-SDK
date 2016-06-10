
//
//  Node.hpp
//  CG
//
//  Created by lewis on 16/6/6.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include "math.h"
#include "TouchDispatcher.h"

/*pointer to function*/
typedef void (Object::*SEL_EventHandler)(Event*);
#define event_selector(_SELECTOR) (SEL_EventHandler)(&_SELECTOR)

class Color{
public:
    Color(unsigned char r, unsigned char g, unsigned char b):r(r), g(g), b(b){}
    unsigned char r, g, b;
};

/*基本节点，用于渲染*/
class Node : public TouchDelegate{
public:
    virtual void setPosition(int x, int y);
    virtual TiPoint getPosition();
    void setVisible(bool visible){m_visible = visible;};
    virtual void draw(){}/*更新渲染*/
    Node *m_next = NULL;
protected:
    int m_posX;/*左上角位置*/
    int m_posY;
    bool m_visible = true;
    int m_width;
    int m_height;
    
    friend class Manager;
};

/*棋盘*/
class CheckerBoard : public Node{
public:
    virtual bool touchBegan(Touch *pTouch, Event *pEvent);
    virtual void draw();
private:

};

/*所有棋子*/
class Piece : public Node{
public:
    virtual void draw();
    
    /*设置x,y棋子为真*/
    void setXY(int x, int y);
    
    /*获得棋盘x,y是否有棋子*/
    bool getXY(int x, int y);
    
    /*检查是否胜利*/
    bool checkWin(int x, int y);
    
    /*设置棋子颜色*/
    void setColor(Color color);
private:
    bool m_piece[15][15] = {0};
    Color m_color = Color(0, 0, 0);/*默认黑色*/
};

/*字体节点*/
class PointFont : public Node{
public:
    static PointFont* create(char *text, int x, int y);
    
    virtual void draw();
    
    void setText(char *text);
private:
    char *m_text = NULL;
};

/*
 *draw node
 *画直线，多边形什么的
 */
class DrawNode : public Node{
public:
    static DrawNode* create(int x, int y);
    virtual void draw();
};

class Manager{
public:
    static Manager* getInstance();
    void addNode(Node *p);
    void removeNode(Node *p);
    void drawScene();
private:
//    Node *m_head;
};
#endif /* Node_hpp */
