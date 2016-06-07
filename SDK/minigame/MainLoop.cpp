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
#include "Gobang.h"

void idleCallback(){
    static clock_t pre = clock();
    
    clock_t current = clock();
    float deltaTime = (current - pre) * 1.0f / CLOCKS_PER_SEC;
    /*每帧间隔t=0.016进行一次重绘 每秒60帧*/
    if (deltaTime > 0.016) {
        /*逻辑处理*/
        logicHandle(deltaTime);
        
        /*渲染*/
        Manager::getInstance()->drawScene();
        glFlush();
        
        pre = current;
    }
}

void registerMainLoop(){
    //空闲回调，程序空闲时就会调用idleCallback函数，它会进行游戏循环
    glutIdleFunc(idleCallback);
}// 空闲回调
