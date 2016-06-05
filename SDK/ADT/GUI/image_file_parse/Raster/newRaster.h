//
//  newRaster.hpp
//  LImage
//
//  Created by lewis on 16/5/12.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef newRaster_hpp
#define newRaster_hpp

#include <stdio.h>

//真正的光栅化操作， raster文件其实是光线跟踪

//世界坐标到模型视图坐标
void worldToModelView();

//设置模型视图矩阵
void setModelViewTransform(float dx, float dy, float dz);
void setModelViewScale(float sx, float sy, float sz);
void setModelViewRotate(float x, float y, float z);//摄像机方向旋转到哪个点

//透视投影
void modelViewToProjection();

void projectionToViewport();


#endif /* newRaster_hpp */
