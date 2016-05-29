//
//  Window.hpp
//  LImage
//
//  Created by lewis on 16/4/27.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <vector>
//用opengl绘制的一套窗口系统
//目标是实现一般应用开发的图形界面

class Window{
public:
    Window(int width, int height);
    
    // 每个窗口自己绘制的方法
    virtual void draw(){}
    
    void show();
    void hide(){};
    
private:
    int m_width;
    int m_height;
    
    int xPos;
    int yPos;
    
    //子窗口
    //m_windows
    
    //每个在opengl窗口中显示的方法，重绘制方法
    void display();
    
    //应用唯一主窗口类
    static Window* mainWindow;
    //所有窗口 opengl会调用它们的绘制函数进行窗口绘制
    static std::vector<Window*> windows;
    //所有窗口绘制，重绘方法
    static void redraw();
};

#endif /* Window_hpp */
