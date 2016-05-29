//
//  LPrint.cpp
//  CG
//
//  Created by 鲁飞 on 16/5/24.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "print.h"

void printChar(char *buf, int length, char *description){
    printf("%s: ", description);
    
    for (int i = 0; i < length; i++) {
        printf(i == length -1 ? "%c\n" : "%c", buf[i]);
    }
}