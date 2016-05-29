//
//  ColorModeDataSection.cpp
//  CG
//
//  Created by 鲁飞 on 16/5/24.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "ColorModeDataSection.h"

void parseColorModeDataSection(ColorModeDataSection *cmds, MutableData *md){
    cmds->lengthOfColorData = md->parseInt();
    printf("cmds->lengthOfColorData: %d\n", cmds->lengthOfColorData);
}