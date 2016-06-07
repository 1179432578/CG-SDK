//
//  Button.hpp
//  CG
//
//  Created by 鲁飞 on 16/6/7.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef Button_hpp
#define Button_hpp

#include <stdio.h>
#include "Node.h"

/*游戏控件*/

class Button : public Node{
public:
    static Button* create(int x, int y, int width, int height, char *text);
    virtual void draw();
private:
    char *m_text;
    char m_width;
    char m_height;
};

#endif /* Button_hpp */
