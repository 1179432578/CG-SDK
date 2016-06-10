//
//  TouchDispatcher.hpp
//  CG
//
//  Created by lewis on 16/6/10.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef TouchDispatcher_hpp
#define TouchDispatcher_hpp

#include <stdio.h>
#include "math.h"

/*base class*/
class Object{
    
};

/*触摸事件分发*/

enum {
    TOUCHBEGAN,
    TOUCHMOVED,
    TOUCHENDED,
    TOUCHCANCELLED,
    
    TouchMax,
};

class Event{
};

class Touch{
public:
    Touch(){}
    TiPoint getLocationInView() const;/*返回视图/屏幕坐标*/
//    Point getDelta() const ;/*返回两点的间隔*/
//    Point getPreviousLocationInView() const;
//    Point getStartLocationInView() const;
    void setTouchInfo(int x, int y)
    {
        m_prevPoint = m_point;
        m_point.x   = x;
        m_point.y   = y;
    }

private:
    TiPoint m_startPoint;
    TiPoint m_point;
    TiPoint m_prevPoint;
};

/*需要实现触摸的结点实现此接口*/
class TouchDelegate : public Object{
public:
    
    TouchDelegate() {}
    
    virtual ~TouchDelegate(){}
    
    virtual bool touchBegan(Touch *pTouch, Event *pEvent) {return false;};
    
    // optional
    virtual void touchMoved(Touch *pTouch, Event *pEvent) {}
    virtual void touchEnded(Touch *pTouch, Event *pEvent) {}
    virtual void touchCancelled(Touch *pTouch, Event *pEvent) {}
    
    TouchDelegate *m_next = NULL;
};


/*触摸事件分发器，暂时没有*/
class TouchDispatcher{
public:
    static TouchDispatcher* getInstance();
    void touch(Touch *pTouch, Event *pEvent, unsigned int uIndex);/*分发触摸事件*/
    void addDelegate(TouchDelegate *d);/*添加一个需要接受触摸事件的实体*/
    void removeDelegate(TouchDelegate *pDelegate);
    
//    virtual void touchesBegan(Touch* touch, CCEvent* pEvent);/*单点, pEvent=nil*/
//    virtual void touchesMoved(Touch* touch, CCEvent* pEvent);
//    virtual void touchesEnded(Touch* touch, CCEvent* pEvent);
////    virtual void touchesCancelled(Touch* touch, CCEvent* pEvent);
    
private:
    TouchDelegate *m_delagates = NULL;/*代理对象链表*/
};
#endif /* TouchDispatcher_hpp */
