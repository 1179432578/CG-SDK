//
//  math.hpp
//  CG
//
//  Created by lewis on 16/6/10.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef math_hpp
#define math_hpp

#include <stdio.h>

class TiPoint{
public:
    TiPoint():x(0), y(0){}
    TiPoint(int x, int y):x(x), y(y){}
public:
    int x, y;
};

#endif /* math_hpp */
