//
//  control.hpp
//  CG
//
//  Created by lewis on 16/6/10.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef control_hpp
#define control_hpp

#include <stdio.h>
#include "Node.h"

/*base control*/

/*button*/
class Button : public Node {
public:
    virtual bool touchBegan(Touch *pTouch, Event *pEvent);
    static Button* create(int x, int y, int width, int height, Object *target, SEL_EventHandler selector);
    virtual void draw();
private:
    SEL_EventHandler m_selector;
    Object *m_target;
};

#endif /* control_hpp */
