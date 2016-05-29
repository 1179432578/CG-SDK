//
//  raster.cpp
//  LImage
//
//  Created by lewis on 16/5/8.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "raster.h"
#include <GLUT/GLUT.h>
#include "ray_polygon_intersection.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

//一开始摄像机坐标系与世界坐标系是重合的，所以可以直接求多边形与射线交点
//如果摄像机移动了，那么就需要把多边形顶点进行变换，求它们在摄像机坐标系中的位置，然后投影到摄像机平面上
//摄像机位置
Vector3 eye(0, 0, 1);
//摄像机方向
Vector3 eyeDirection(0, 0, -1);
//摄像机投影平面原点
Vector3 perpectiveProjectionPlaneOrigin(0, 0, 0);

//下面转化应该有顶点向量乘以矩阵进行变换的，下次修改
//把多边形的顶点由世界坐标转换为视图坐标
void worldToView(Vector3 a[], int n){
    for (int i = 0; i < n; i++) {
        //next implement
    }
}

//init raster system
RasterArgv *raster_argv;
void initRasterSystem(){
    raster_argv = new RasterArgv;
    memset(raster_argv, 0, sizeof(RasterArgv));
    
    raster_argv->viewpoint = Vector3(0.0f, 0.0f, 0.0f);
}

void enableLineBox(){
    if (!raster_argv) {
        // error
    }
    
    raster_argv->bEnableLineBox = true;
}

//把视口上的一个光栅化点转换为投影平面上的一个浮点坐标
void viewPortPointToProjectionPlanePoint(Vector3 &p){
    p.x = p.x / 480 * 2 - 1.0f;
    p.y = p.y / 360 * 2 - 1.0f;
    p.z = 0.0f;
}

//求眼睛穿过投影平面上的一点与多边形的交点,该点在投影面上显示
//p是投影平面上的点向量
Vector3 getProjectionPoint(Vector3 &p, Vector3 a[], int n){
    Vector3 normal = Vector3::vec3Cross(Vector3::vec3Sub(a[1], a[0]), Vector3::vec3Sub(a[2], a[0]));
    
    Vector3 intersection = calculateRayAndPlaneIntersection(eye, Vector3::vec3Add(eyeDirection, p), a[0],
                                     normal);//平面法向量需要求出来，这里直接给出，下次修改
    
    //这个函数计算存在很大问题
    if (isIntersectionInPolygen(a, n, intersection)) {
        return intersection;
    }
    
    //表示不存在 需要修改
    return Vector3(1000, 1000, 1000);
}

//检测点是否在多边形的线框中
bool isPointInLineBox(Vector3 a[], int n, Vector3 &p){
    Vector3 p1p2;//线段向量
    Vector3 p1p;//p到线段顶点p1的向量
    Vector3 cross;//p1p2与p1p的叉积
    
    for (int i = 0; i < n; i++) {
        p1p2 = Vector3::vec3Sub(a[(i+1)%n], a[i]);
        p1p = Vector3::vec3Sub(p, a[i]);
        cross = Vector3::vec3Cross(p1p2, p1p);
        
        //在一条直线上
        const float PRECISION = 0.01;
        if (fabsf(cross.x) < PRECISION && fabsf(cross.y) < PRECISION && fabsf(cross.z) < PRECISION) {
            float dx = fabsf(a[(i+1)%n].x - a[i].x);
            float dx1 = fabsf(p.x - a[(i+1)%n].x);
            float dx2 = fabsf(p.x - a[i].x);
            
            float dy = fabsf(a[(i+1)%n].y - a[i].y);
            float dy1 = fabsf(p.y - a[(i+1)%n].y);
            float dy2 = fabsf(p.y - a[i].y);
            
            float dz = fabsf(a[(i+1)%n].z - a[i].z);
            float dz1 = fabsf(p.z - a[(i+1)%n].z);
            float dz2 = fabsf(p.z - a[i].z);
            
            //在线段上
            const float PRECISION2 = 0.02;
            if (fabsf(dx - dx1 - dx2) < PRECISION2 &&
                fabsf(dy - dy1 - dy2) < PRECISION2 &&
                fabsf(dz - dz1 - dz2) < PRECISION2) {
                return true;
            }
        }
        
    }
    
    return false;
}
//简化的光栅化函数
void raster(Vector3 a[], int n, int width, int height){
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            //视口上面的一点
            Vector3 p = Vector3(column * 1.0f, row * 1.0f, 0.0f);
            
            //把视口上的一点转换为投影平面上的一点
            viewPortPointToProjectionPlanePoint(p);
            
            //多边形在投影平面上的投影点
            Vector3 projectionPoint = getProjectionPoint(p, a, n);
            
            //边界点没了 需要修一下
            //printf("<%d, %d> => (%f, %f, %f)\n",column, row, projectionPoint.x, projectionPoint.y , projectionPoint.z);
            if (projectionPoint.x == 1000.0f) {
                continue;
            }
            
            //线框模式
            if (raster_argv->bEnableLineBox) {
                if (isPointInLineBox(a, n, projectionPoint)) {
                    glBegin(GL_POINTS);
                    glVertex2f(projectionPoint.x, projectionPoint.y);
                    glEnd();
                }
            }
            else{
                glBegin(GL_POINTS);
                glVertex2f(projectionPoint.x, projectionPoint.y);
                glEnd();
            }
        }//for
    }//for
}

void setViewPort(int width, int height){
    raster_argv->viewport_width = width;
    raster_argv->viewport_height = height;
}

//平移摄像机 后面改成向量与矩阵乘 不在手动计算
//viewpoint是摄像机在世界中的位置
void translateViewpoint(float dx, float dy, float dz){
    raster_argv->viewpoint.x = raster_argv->viewpoint.x + dx;
    raster_argv->viewpoint.y = raster_argv->viewpoint.y + dy;
    raster_argv->viewpoint.z = raster_argv->viewpoint.z + dz;
    //printf("%f %f %f\n", raster_argv->viewpoint.x, raster_argv->viewpoint.y, raster_argv->viewpoint.z);
}

//平移多边形，摄像机平移后，所有的多边形在摄像机坐标系中的坐标发生率为变化
Vector3* translatePolygon(Vector3 a[], int n){
    Vector3 *ret = new Vector3[n];
    
    for (int i = 0; i < n; i++) {
        ret[i].x = a[i].x - raster_argv->viewpoint.x;
        ret[i].y = a[i].y - raster_argv->viewpoint.y;
        ret[i].z = a[i].z - raster_argv->viewpoint.z;
    }
    
    return ret;
}



//--------------------------draw----------------------------//
//draw with polygon
void drawPolygon(Vector3 a[], int n){
    for (int row = 0; row < 360; row++) {
        for (int column = 0; column < 480; column++) {
            //视口上面的一点
            Vector3 p = Vector3(column * 1.0f, row * 1.0f, 0.0f);
            
            //把视口上的一点转换为投影平面上的一点
            viewPortPointToProjectionPlanePoint(p);
            
            //世界坐标到模型视图坐标变换
            Vector3 *newa = translatePolygon(a, n);
            
            //模型视图坐标到投影平面坐标变换
            Vector3 projectionPoint = getProjectionPoint(p, newa, n);
            
            //投影平面坐标到视口坐标变换
            
            //边界点没了 需要修一下
            //printf("<%d, %d> => (%f, %f, %f)\n",column, row, projectionPoint.x, projectionPoint.y , projectionPoint.z);
            
            //这里表示不存在与投影平面相交的一点
            if (projectionPoint.x == 1000.0f) {
                continue;
            }
            
            //线框模式
            if (raster_argv->bEnableLineBox) {
                if (isPointInLineBox(newa, n, projectionPoint)) {
                    glBegin(GL_POINTS);
                    glVertex2f(projectionPoint.x, projectionPoint.y);
                    glEnd();
                }
            }
            else{
                glBegin(GL_POINTS);
                glVertex2f(projectionPoint.x, projectionPoint.y);
                glEnd();
            }
            
            delete [] newa;
            
            
        }//for
    }//for
}
