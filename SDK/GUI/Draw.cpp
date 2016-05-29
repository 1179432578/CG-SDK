//
//  Draw.cpp
//  LImage
//
//  Created by lewis on 16/4/27.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "Draw.h"
#include <GLUT/glut.h>
#include <stdio.h>

void redraw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glFlush();
    
    glPointSize(2.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    
    glBegin(GL_POINTS);
    
    glVertex2f(0.8f, 0.4f);
    glVertex2f(1.0f, 0.6f);
    
    glEnd();
    
    glFlush();
}

void Draw::createWindow(int width, int height){
    int argc = 1;
    char *argv = "init";
    char **argvv = &argv;
    glutInit(&argc, argvv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize (width, height);
    glutInitWindowPosition (1920 / 2 - width / 2, 1080 / 2 - height / 2);
    glutCreateWindow ("GLO2 2D Game Enginer");
    
    glutDisplayFunc(redraw);
    
    glutMainLoop();
}

void Draw::drawPixel(int x, int y){
    printf("ereryr666666");
    glPointSize(2.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    
    glBegin(GL_POINTS);
    
    glVertex2f(0.8f, 0.4f);
    glVertex2f(1.0f, 0.6f);
    
    glEnd();
    
    glFlush();
}