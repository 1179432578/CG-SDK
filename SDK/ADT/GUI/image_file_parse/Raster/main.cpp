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
#include "mgl.h"
#include "Gobang.h"


int main(int argc, const char * argv[]) {
    mglInit(argc, (char**)argv, 800, 800);
    
    initGame();
    
    /*启动循环*/
    mglMainLoop();
    
    return 0;
}
