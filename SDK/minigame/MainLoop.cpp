//
//  MainLoop.cpp
//  CG
//
//  Created by lewis on 16/6/6.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "MainLoop.h"
#include <GLUT/GLUT.h>
#include <time.h>
#include "Node.h"

void idleCallback(){
    static clock_t pre = clock();
    
    //每帧间隔t=0.016进行一次重绘 每秒60帧
    if (clock() - pre > 0.016 * CLOCKS_PER_SEC) {
        pre = clock();
        
        Manager::getInstance()->drawScene();
        glFlush();
    }
}

void registerMainLoop(){
    //空闲回调，程序空闲时就会调用idleCallback函数，它会进行游戏循环
    glutIdleFunc(idleCallback);
}// 空闲回调
