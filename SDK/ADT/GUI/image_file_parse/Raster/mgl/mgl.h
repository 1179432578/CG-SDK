//
//  mgl.hpp
//  CG
//
//  Created by lewis on 16/6/5.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef mgl_hpp
#define mgl_hpp

#include <stdio.h>
#include <GLUT/GLUT.h>
#include "Node.h"

/*3d interface*/
typedef int MGLenum;
#define MGL_FRONT 1000
#define MGL_COLOR_BUFFER_BIT               0x00004000

extern int *FBO;

/*select a color buffer source for pixels*/
void mglReadBuffer(MGLenum);

/*init mgl*/
void mglInit(int argc, char * argv[], int width, int height);

void mglMainLoop();

/*write pixels to screen*/
void mglDisplay();

/*指定清楚帧缓存FBO的颜色值*/
void mglClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

/*清楚帧缓存，帧缓存：颜色、模板、深度、？？？*/
void mglClear (GLbitfield mask);

/*vertex color*/
void mglColor(float r, float g, float b, float a);

/*2d interface*/
/*set draw color*/
void mglSetColor(float r, float g, float b, float a);

/*draw pixel at cooridate(x, y)*/
inline void mglDrawPixel(int x, int y);

/*draw line*/
void mglLineTo(int x, int y);
void mglMoveTo(int x, int y);

/*draw circle*/
void mglDrawCircle(int x, int y, int radius);
void mglFillCircle(int x, int y, int r);
/*draw arc*/

/*draw rectangle*/
void mglDrawRectangle(int x, int y, int width, int height);/*xy左上角*/

/*
 *水平渐变
 *draw rectangle with gradient color
 */
void mglDrawGradientRectangleTest(int x, int y, int width, int height, Color s, Color f);/*xy左上角*/

#endif /* mgl_hpp */
