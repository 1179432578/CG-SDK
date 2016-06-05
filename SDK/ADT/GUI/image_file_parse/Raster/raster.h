//
//  raster.hpp
//  LImage
//
//  Created by lewis on 16/5/8.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef raster_hpp
#define raster_hpp
#include "Vector3.h"

//光栅化配置参数
typedef struct RasterArgv{
    bool bEnableLineBox;
    int viewport_width;
    int viewport_height;
    
    Vector3 viewpoint;
}RasterArgv;

extern RasterArgv *raster_argv;

/******************光栅化操作函数组*******************/
//init raster system
void initRasterSystem();

//open linebox model
void enableLineBox();

//set viewport
void setViewPort(int width, int height);

//draw line

//draw circle

//draw with triangle

//draw with polygon
void drawPolygon(Vector3 a[], int n);

//进行光栅化
void raster(Vector3 a[], int n, int width, int height);

//移动摄像机
void translateViewpoint(float dx, float dy, float dz);

//缩放摄像机这个操作暂不定义

//旋转摄像机， 把摄像机眼睛方向向量转到一个指定位置，求出旋转向量与旋转角度，
//这样每个顶点可以根据这两个变量求出旋转后在摄像机中的位置

/****************************************************/


#endif /* raster_hpp */
