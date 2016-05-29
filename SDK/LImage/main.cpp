//
//  main.cpp
//  LImage
//
//  Created by lewis on 16/4/19.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "MutableData.h"
#include "LBitmap.h"
#include "HashTable.h"
#include "CCDictionary.h"
#include "Draw.h"
#include "Window.h"
#include <GLUT/glut.h>
#include "Vector3.h"
#include "ray_polygon_intersection.h"
#include "raster.h"
#include <GLUT/glut.h>
#include "Matrix.h"
#include <math.h>
#include "matrix_transform.h"
#include "LPsdParser.h"

void draw(){
//    Vector3 a[8] = {Vector3(-0.9, 0.9, 0), Vector3(0.9, 0.9, 0), Vector3(0.9, -0.9, 0),
//        Vector3(0.5, -0.9f, 0), Vector3(0.5f, 0.0f, 0.0f), Vector3(-0.5f, 0.0f, 0.0f), Vector3(-0.5f, -0.9f, 0.0f),
//                    Vector3(-0.9, -0.9, 0)};
    
    //z当前只能是0，因为现在是手动指定的面的法向量(0, 0, 1)
    int n = 5;
    //顶点数组
    Vector4 vertex[8] = {Vector4{-9, 9, -12, 1}, Vector4{9, 9, -12, 1}, Vector4{9, -9, -12, 1}, Vector4{-9, -9, -12, 1},
        Vector4{9, 9, -30, 1}, Vector4{9, -9, -30, 1}, Vector4{-9, -9, -30, 1}, Vector4{-9, 9, -30, 1}};
    
    //索引数组
    int index[36]= {
        //前面
        0,1,2, 0,2,3,
        //后面
        4,5,6, 4,6,7,
        //上面
        0,1,4, 0,4,7,
        //下面
        2,3,6, 2,5,6,
        //左面
        0,3,6, 0,6,7,
        //右面
        1,2,5, 1,4,5
    };
    Vector4 b[5] = {Vector4{-9, 9,  -30.0f, 1}, Vector4{9, 9, -30.0, 1.0}, Vector4{9.0f, -9.0f, -30.0f, 1.0f},
                    Vector4{9, 9,  -12.0f, 1}, Vector4{9, -9,  -12.0f, 1}};
//    int n = 3;
//    Vector4 b[3] = {Vector4{9, 9, -30.0, 1.0}, Vector4{9.0f, -9.0f, -30.0f, 1.0f},
//        Vector4{9, 9,  -12.0f, 1}};

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0, 1, 1);
    
    testVertexTransform(vertex, 8);
//    raster(a, sizeof(a) / sizeof(Vector3), 480, 360);
//    
//    drawPolygon(b, sizeof(b) / sizeof(Vector3));
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 36; i++) {
        glVertex2f(vertex[index[i]].x, vertex[index[i]].y);
    }
    glEnd();
    glFlush();
    
}

int main(int argc, const char * argv[]) {
//    glutInit(&argc, (char **)argv);
//    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
//    glutInitWindowSize (480, 360);
//    glutInitWindowPosition (1920 / 2, 1080 / 2);
//    glutCreateWindow ("GUI");
//    glutDisplayFunc(draw);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glutMainLoop();
    
    testPsdParser();

    return 0;
}
