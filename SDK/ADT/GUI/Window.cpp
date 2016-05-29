//
//  Window.cpp
//  LImage
//
//  Created by lewis on 16/4/27.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "Window.h"
#include <GLUT/glut.h>

//NULL...
Window* Window::mainWindow = 0;
std::vector<Window*> Window::windows ;

Window::Window(int width, int height){
    if (!mainWindow) {
        mainWindow = this;
        
        int argc = 1;
        char *argv = "init";
        char **argvv = &argv;
        glutInit(&argc, argvv);
        glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
        glutInitWindowSize (width, height);
        glutInitWindowPosition (1920 / 2 - width / 2, 1080 / 2 - height / 2);
        glutCreateWindow ("GLO2 2D Game Enginer");
        glutDisplayFunc(Window::redraw);
        //进入事件循环了
        //glutMainLoop();
        //glutReshapeFunc(ReshapeFunc);
    }
    
    m_width = width;
    m_height = height;
    windows.push_back(this);
}

void Window::show(){

}

void Window::display(){
    //绘制窗口
    printf("%d display", this);
    
    glPointSize(50.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    
    glBegin(GL_LINE_LOOP);
    
    glVertex2f(-m_width/800.0f + 0.1f, m_height/600.0f- 0.1f);
    glVertex2f(-m_width/800.0f+ 0.1f, -m_height/600.0f+ 0.1f);
    glVertex2f(m_width/800.0f- 0.1f, -m_height/600.0f+ 0.1f);
    glVertex2f(m_width/800.0f- 0.1f, m_height/600.0f- 0.1f);
    
    glEnd();
    
    //调用客户自定义绘制函数
    draw();
    
//    glFlush();
}

//static
void Window::redraw(){
    glClearColor(192.0f/255.0f, 192.0f/255.0f, 192.0f/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i=0; i<windows.size(); i++) {
        windows[i]->display();
    }
    
    glFlush();
}