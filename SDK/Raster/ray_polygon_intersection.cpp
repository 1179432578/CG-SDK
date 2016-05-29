//
//  Ray_Polygon_Intersection.cpp
//  LImage
//
//  Created by lewis on 16/5/4.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "ray_polygon_intersection.h"
#include <stdio.h>
#include <math.h>

//平面方程(p1 - p) dot n = 0
//射线参数方程p = e + td
Vector3 calculateRayAndPlaneIntersection(const Vector3 &rayStartPoint, const  Vector3 &rayDirection, const Vector3 &pointInPlane,
                                         const Vector3 &planeNormal){
    // t>0在射线前面
    float t = Vector3::vec3Dot(Vector3::vec3Sub(pointInPlane, rayStartPoint), planeNormal) / Vector3::vec3Dot(rayDirection, planeNormal);
    
    return Vector3::vec3Add(rayStartPoint, Vector3::vec3Scale(rayDirection, t));
}

//这个函数最重要了 判断射线跟线段是否相交
//射线跟线段是否相交
//p = p1 + t(p2-p1) p1、p2线段顶点，t是p2p1向量长度系数，p是交点
//(p-s) cross d = 0向量 s是射线开始点， d是射线方向向量
bool isRayAndSegmentIntersection(Vector3 &segP1, Vector3 &segP2, Vector3 rayStartPoint, const Vector3 &rayDirection){
    Vector3 p2p1 = Vector3::vec3Sub(segP2, segP1);
    Vector3 d = rayDirection;

    //射线与线段平行,那么修改射线方向
    //p1p2 cross d = 0向量
    if (Vector3::vec3Cross(p2p1, rayDirection).y == 0.0f &&
        Vector3::vec3Cross(p2p1, rayDirection).z == 0.0f &&
        Vector3::vec3Cross(p2p1, rayDirection).x == 0.0f) {
        d = Vector3(0.0f, 1.0f, 0.0f);
    }
    
    //求两线端交点
    //http://www.zhihu.com/question/19971072
    float t = Vector3::vec3Divide(Vector3::vec3Cross(Vector3::vec3Sub(rayStartPoint, segP1), rayDirection), Vector3::vec3Cross(p2p1, rayDirection));

    
    //const float EPSINON = 0.0000001f;
    if (t > 0.0f && t < 1.0f) {
        //printf("t:%f\n", t);
        //交点在射线上
        Vector3 intersectionP = Vector3::vec3Add(segP1, Vector3::vec3Scale(p2p1, t));
        Vector3 ps = Vector3::vec3Sub(intersectionP, rayStartPoint);
        
        if (Vector3::vec3Dot(d, ps) >= 0.0f) {
            return true;
        }
        
    }
    
    return false;
}

bool isIntersectionInPolygen(Vector3 a[], int n, const Vector3 &intersction){
    int intersctionCount = 0;
    for (int i = 0; i < n; i++) {
        //方向向量是Vector3(1.0f, 0.0f, 0.0f)
        if(isRayAndSegmentIntersection(a[i], a[(i+1)%n], intersction, Vector3(1.f, 0.0f, 0.0f))){
            intersctionCount++;
        }
    }
    
    //printf("%d\n", intersctionCount);
    //如果奇数个交点那么一定在多边形里
    return intersctionCount % 2 == 0 ? false : true;
}
