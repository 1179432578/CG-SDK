//
//  text.hpp
//  CG
//
//  Created by lewis on 16/6/5.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef text_hpp
#define text_hpp

#include <stdio.h>
#include "mgl.h"

/*简单的绘制文本api*/
void drawText(const char *str, int x, int y);

/*解析出字体*/
void parseFontFile(char *filename);

#endif /* text_hpp */
