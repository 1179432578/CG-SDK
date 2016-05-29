//
//  Ray_Polygon_Intersection.hpp
//  LImage
//
//  Created by lewis on 16/5/4.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef Ray_Polygon_Intersection_hpp
#define Ray_Polygon_Intersection_hpp

#include "Vector3.h"

//求3d空间射线与任意多边形的交点
//用于确定像平面里的一个像素点，这个当前未实现，需要进一步探索

//计算射线与平面交点
Vector3 calculateRayAndPlaneIntersection(const Vector3 &rayStartPoint, const  Vector3 &rayDirection, const Vector3 &pointInPlane,
                                         const Vector3 &planeNormal);

//计算射线与线段是否相交
bool isRayAndSegmentIntersection(Vector3 &segP1, Vector3 &segP2, Vector3 rayStartPoint, Vector3 &rayDirection);

//判断交点是否在多边形内 a:多边形顶点数组，按次序的，任意相邻两点构成多边形的一条边
bool isIntersectionInPolygen(Vector3 a[], int n, const Vector3 &intersction);

#endif /* Ray_Polygon_Intersection_hpp */
