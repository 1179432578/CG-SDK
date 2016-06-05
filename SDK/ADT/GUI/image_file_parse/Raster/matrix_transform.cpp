//
//  matrix_transform.cpp
//  LImage
//
//  Created by lewis on 16/5/15.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "matrix_transform.h"
#include <GLUT/GLUT.h>

Matrix44 translate(float dx,float dy, float dz){
    Matrix44 ret = {0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        dx, dy, dz, 1};
    
    return ret;
}

Matrix44 normalizeMatrix(){
    Matrix44 ret = {1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1};
    
    return ret;
}

Matrix44 rotate(float angle, float a, float b, float c){
    //绕x轴旋转
    if (b == 0.0f && c == 0.0f) {
        float costheta = cosf(angle);
        float sintheta = sinf(angle);
        Matrix44 rx = {1, 0, 0, 0,
            0, costheta, sintheta, 0,
            0, -sintheta, costheta, 0,
            0, 0, 0, 1};
        
        return rx;
    }
    
    Matrix44 ret = normalizeMatrix();
    //1 绕x轴旋转alfa与XOZ面重合
    float length = sqrtf(b*b + c*c);
    float cosalfa = c / length;
    float sinalfa = b / length;
    Matrix44 rx = {1, 0, 0, 0,
        0, cosalfa, sinalfa, 0,
        0, -sinalfa, cosalfa, 0,
        0, 0, 0, 1};
    
    ret = multiply(&ret, &rx);
    
    //2 绕Y轴旋转-belta与Z轴重合
    float length2 = sqrtf(a*a + b*b + c*c);
    float sinbelta = a / length2;
    float cosbelta = length / length2;
    Matrix44 ry = {cosbelta, 0, -sinbelta, 0,
        0, 1, 0, 0,
        sinbelta, 0, cosbelta, 0,
        0, 0, 0, 1};
    
    ret = multiply(&ret, &ry);
    
    //3 绕Z轴旋转theta=angle
    float costheta = cosf(angle);
    float sintheta = sinf(angle);
    Matrix44 rz = {costheta, sintheta, 0, 0,
        -sintheta, costheta, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1};
    ret = multiply(&ret, &rz);
    
    //4 绕Y轴旋转belta
    Matrix44 ry2 = {cosbelta, 0, sinbelta, 0,
        0, 1, 0, 0,
        -sinbelta, 0, cosbelta, 0,
        0, 0, 0, 1};
    
    ret = multiply(&ret, &ry2);
    
    //5 绕x轴旋转-alfa
    Matrix44 rx2 = {1, 0, 0, 0,
        0, cosalfa, -sinalfa, 0,
        0, sinalfa, cosalfa, 0,
        0, 0, 0, 1};
    
    ret = multiply(&ret, &rx2);
    
    return ret;
}

Matrix44 mglLookAt(float eyeX,float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ){
    //观察坐标系的z轴负方向，即是观察方向
    Vector3 direction(centerX - eyeX, centerY - eyeY, centerZ - eyeZ);
    direction.normalize();
//    printf("%f %f %f", direction.x, direction.y, direction.z);
    
    //右方向，x轴正向
    Vector3 right = Vector3::vec3Cross(direction, Vector3(upX-eyeX, upY-eyeY, upZ-eyeZ));
    right.normalize();
    
    //上方向，y轴正向
    Vector3 up = Vector3::vec3Cross(right, direction);
    
    Matrix44 ret = { right.x, up.x, -direction.x, 0,
                     right.y, up.y, -direction.y, 0,
                     right.z, up.z, -direction.z, 0,
                     0, 0, 0, 1};
    
    //用于行向量
    Matrix44 t = {1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, 1, 0,
                  -eyeX, -eyeY, -eyeZ, 1};
    
    ret = multiply(&t, &ret);
    
    return ret;
}

//n = zMIn, f = zMax
Matrix44 mgluPerspective(float fovy, float aspect, float zMin, float zMax){
    float yMax = zMin * tanf(fovy * 0.5f);
    float yMin = -yMax;
    float xMin = yMin * aspect;
    float xMax = -xMin;
    
    //用于行向量
    Matrix44 ret = {(2.0f * zMin) / (xMax - xMin), 0, 0,0,
                    0, (2.0f * zMin) / (yMax - yMin), 0, 0,
                    (xMax + xMin) / (xMax - xMin), (yMax + yMin) / (yMax - yMin), -((zMax + zMin) / (zMax - zMin)), -1.0f,
                    0, 0,-((2.0f * (zMax*zMin))/(zMax - zMin)), 0};
    
    //用于列向量
//    Matrix44 ret = {(2.0f * zMin) / (xMax - xMin), 0, (xMax + xMin) / (xMax - xMin), 0,
//        0, (2.0f * zMin) / (yMax - yMin), (yMax + yMin) / (yMax - yMin), 0,
//        0, 0, -((zMax + zMin) / (zMax - zMin)), -((2.0f * (zMax*zMin))/(zMax - zMin)),
//        0, 0, -1.0f, 0};

    return ret;
}
//不在对z进行变换，因为在投影变换时，已经对z进行变换让它存放深度信息了
Matrix44 mglViewport(int l, int b, int width, int height){
    Matrix44 ret = { width/2.0f, 0, 0, 0,
                     0, height/2.0f, 0, 0,
                     0, 0, 1, 0,
                     width/2.0f + l, height/2.0f+b, 0, 1};
    
    return ret;
}

void testVertexTransform(Vector4 vertex[], int n){
    Matrix44 modelviewM, projectionM, M;
    
    modelviewM = mglLookAt(20, 30, 10, 0, 0, 0, 20, 31, 1);
    projectionM = mgluPerspective(M_PI_2, 1.0f, 1.0f, 1000.0f);
    M = multiply(&modelviewM, &projectionM);
    
    float w;
//    //模型视图变换
//    for (int i = 0; i < n; i++) {
//        vertex[i] = multiply(&vertex[i], &modelviewM);
//    }
//    
//    //投影变换
//    for (int i = 0; i < n; i++) {
//        vertex[i] = multiply(&vertex[i], &projectionM);
//    }
//    
//    //透视除法
    for (int i = 0; i < n; i++) {
        vertex[i] = multiply(&vertex[i], &M);
        w = vertex[i].w;//w = -z
        vertex[i].x = vertex[i].x / w;
        vertex[i].y = vertex[i].y / w;
//        vertex[i].z = vertex[i].z / w;
    }
}

/*测试光栅效果*/
void testRaster(){
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

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0, 1, 1);

    testVertexTransform(vertex, 8);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 36; i++) {
        glVertex2f(vertex[index[i]].x, vertex[index[i]].y);
    }
    glEnd();
    glFlush();

}