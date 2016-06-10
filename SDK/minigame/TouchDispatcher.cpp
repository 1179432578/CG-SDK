//
//  TouchDispatcher.cpp
//  CG
//
//  Created by lewis on 16/6/10.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "TouchDispatcher.h"

TiPoint Touch::getLocationInView() const{
    return m_point;
}

TouchDispatcher* TouchDispatcher::getInstance(){
    static TouchDispatcher *ret = NULL;
    
    if (!ret) {
        ret = new TouchDispatcher;
    }
    
    return ret;
}


/*省去TouchHandle，直接使用TouchDelegate*/
/*当前给每个对象都发began事件，自己判断是否需要，需要了此点，后续此点的移动、结束事件也会发给它
 *后面加入zorder代表优先级，越大越先接收到began事件。
 */
static TouchDelegate *td = NULL;/*当前接受触摸的对象*/
void TouchDispatcher::touch(Touch *pTouch, Event *pEvent, unsigned int uIndex){
    TouchDelegate *delegate = m_delagates;
    while (delegate) {/*遍历每一个触摸对象*/
        bool bClaimed = false;
        
        if (uIndex == TOUCHBEGAN) {/*只能每次一个对象需要处理点*/
            td = NULL;/*protect bug*/
            bClaimed = delegate->touchBegan(pTouch, pEvent);
            
            if (bClaimed) {
                td = delegate;
                break;
            }
        }
        else if (td){
            switch (uIndex)
            {
                case TOUCHMOVED:
                    delegate->touchMoved(pTouch, pEvent);
                    break;
                case TOUCHENDED:
                    delegate->touchEnded(pTouch, pEvent);
                    td = NULL;
                    break;
                case TOUCHCANCELLED:
                    delegate->touchCancelled(pTouch, pEvent);
                    break;
            }
            break;
        }
        else{
            break;
        }
        
        delegate = delegate->m_next;
    }
}

void TouchDispatcher::addDelegate(TouchDelegate *d){
    d->m_next = m_delagates;
    m_delagates = d;
}
                                  
void TouchDispatcher::removeDelegate(TouchDelegate *pDelegate){

}
