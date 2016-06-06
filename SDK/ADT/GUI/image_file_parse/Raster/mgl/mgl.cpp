//
//  mgl.cpp
//  CG
//
//  Created by lewis on 16/6/5.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "mgl.h"
#include <string.h>
#include <math.h>

static int WIDTH, HEIGHT;
static GLuint TEX;
int *FBO = NULL;

/*初始化mgl，需要在opengl初始化结束后再调用*/
void mglInit(int argc, char * argv[], int width, int height){
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize (width, height);
    glutInitWindowPosition (1920 / 2, 1080 / 2);
    glutCreateWindow ("GUI");
    glEnable(GL_TEXTURE_2D);
    
    //glutDisplayFunc(draw);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    WIDTH = width;
    HEIGHT = height;
    FBO = new int[WIDTH*HEIGHT];//RGBA每个分量一个字节
    memset(FBO, 0, WIDTH*HEIGHT*4);
    
    glGenTextures(1, &TEX);
    glActiveTexture(GL_TEXTURE0);//一直处于激活状态
    glBindTexture(GL_TEXTURE_2D, TEX);
    
    //纹理参数设置
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
}

void mglMainLoop(){
    glutMainLoop();
}

/**/
void mglDisplay(){
    //设置GL_TEXTURE0纹理GL_TEXTURE_2D数据
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, FBO);
    
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    
    glVertex2f(1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    
    glVertex2f(1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    
    glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glEnd();
    glFlush();
}

static int CLEARCOLOR;
void mglClearColor (GLclampf R, GLclampf G, GLclampf B, GLclampf A){
    CLEARCOLOR = ((int)(R * 255)) + ((int)(G * 255) << 8) + ((int)(B * 255) << 16) + ((int)(A * 255) << 24);
}

void mglClear (GLbitfield mask){
    //清除颜色帧缓存
    if(MGL_COLOR_BUFFER_BIT && mask){
        for (int x=0; x<WIDTH; x++) {
            for (int y=0; y<HEIGHT; y++) {
                FBO[y*WIDTH+x] = CLEARCOLOR;
            }
        }
    }
}

static int COLOR = 0xffffffff;//默认白色
void mglColor(float r, float g, float b, float a){
    COLOR = ((int)(r * 255)) + ((int)(g * 255) << 8) + ((int)(b * 255) << 16) + ((int)(a * 255) << 24);
}


/*************222222222222222222ddddddddddddddddddd***************************/

void mglSetColor(float r, float g, float b, float a){
    mglColor(r, g, b, a);
}

/*左上角00*/
void mglDrawPixel(int x, int y){
    if (y >= HEIGHT || y <0 || x >= WIDTH || x < 0) {
        return;
    }
    FBO[y*WIDTH + x] = COLOR;
}

static int startX = 0;
static int startY = 0;
void mglMoveTo(int x, int y){
    startX = x;
    startY = y;
}

/*增量法画直线DDA*/
//dy = dx*k = 1*k =k
void mglLineTo(int x, int y){
    float sx, sy, fx, fy;
    
    if (startX < x) {
        sx = startX;
        sy = startY;
        fx = x;
        fy = y;
    }
    else if(startX > x) {
        sx = x;
        sy = y;
        fx = startX;
        fy = startY;
    }
    /*垂直*/
    else{
        int ymin = startY < y ? startY : y;
        int ymax = startY < y ? y : startY;
        for(int y=ymin; y<=ymax; y++){
            mglDrawPixel(startX, y);
        }
        return;
    }
    
    /*倾斜*/
    float dy = fy - sy;
    float dx = fx - sx;
    float k = dy / dx;
    float yy = sy;
    for(int x=sx; x<=fx; x++){
        mglDrawPixel(x, roundf(yy));
        yy += k;
    }
}

/*中点线画直线*/


/*画出8个对称点*/
void circle(int x, int y, int dx, int dy){
    mglDrawPixel(x + dx, y + dy);
    mglDrawPixel(y + dx, x + dy);
    mglDrawPixel(-x + dx, y + dy);
    mglDrawPixel(-y + dx, x + dy);
    mglDrawPixel(-x + dx, -y + dy);
    mglDrawPixel(-y + dx, -x + dy);
    mglDrawPixel(x + dx, -y + dy);
    mglDrawPixel(y + dx, -x + dy);
}

/*中点扫描画圆*/
void mglDrawCircle(int cx, int cy, int radius){
    /*画第一个点（x, y+radius）与另外7个对称点*/
    circle(0, radius, cx, cy);
    
    /*确定下一点的中点(x+1, y+radius-1/2)带入f(x,y)=x^2+y^2-R^2=d*/
    float d = 5.0f / 4.0f - radius;
    
    /*画1/8圆*/
    int px = 0;
    int py = radius;
    while (py > px) {
        /*画点(px+1, py)*/
        if (d < 0) {
            d += 2 * px + 3;
        }
        /*画点(px+1,py-1)*/
        else{
            d += 2 * (px - py) + 5;
            py--;
        }
        px++;
        /*画出8个对称点*/
        circle(px, py, cx, cy);
    }
}

// 基于 Bresenham 算法画填充圆
void mglFillCircle(int x, int y, int r)
{
    int tx = 0, ty = r, d = 3 - 2 * r, i;
    
    while( tx < ty)
    {
        // 画水平两点连线(<45度)
        for (i = x - ty; i <= x + ty; i++)
        {
            mglDrawPixel(i, y - tx);
            if (tx != 0)	// 防止水平线重复绘制
                mglDrawPixel(i, y + tx );
        }
        
        if (d < 0)			// 取上面的点
            d += 4 * tx + 6;
        else				// 取下面的点
        {
            // 画水平两点连线(>45度)
            for (i = x - tx; i <= x + tx; i++)
            {
                mglDrawPixel(i, y - ty);
                mglDrawPixel(i, y + ty);
            }
            
            d += 4 * (tx - ty) + 10, ty--;
        }
        
        tx++;
    }
    
    if (tx == ty)			// 画水平两点连线(=45度)
        for (i = x - ty; i <= x + ty; i++)
        {
            mglDrawPixel(i, y - tx);
            mglDrawPixel(i, y + tx);
        }
}
