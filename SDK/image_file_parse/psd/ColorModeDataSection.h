//
//  ColorModeDataSection.hpp
//  CG
//
//  Created by 鲁飞 on 16/5/24.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef ColorModeDataSection_hpp
#define ColorModeDataSection_hpp

#include <stdio.h>
#include "MutableData.h"

struct ColorModeDataSection{
//    4
//    The length of the following color data.
    int lengthOfColorData;
    
//    Variable
//    The color data.
    char *colorData;
};

void parseColorModeDataSection(ColorModeDataSection *cmds, MutableData *md);

#endif /* ColorModeDataSection_hpp */
