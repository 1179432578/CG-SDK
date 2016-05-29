//
//  LBitmap.cpp
//  LImage
//
//  Created by lewis on 16/4/21.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "LBitmap.h"
#include "MutableData.h"

void LBitmap::parseFromFile(char *bitmapName){
    MutableData d;
    
    d.readFile(bitmapName);
    //bmp文件头14个字节
    char *buf = d.parseChars(2);
    printf("type:%c%c\n", buf[0], buf[1]);
    
    int size = d.parseInt();
    printf("size:%d\n", size);
    
    short reserverd1 = d.parseShort();
    short resetverd2 = d.parseShort();
    printf("r1:%d, r2:%d\n", reserverd1, resetverd2);
    
    //位图数据的偏移
    int offBits = d.parseInt();
    printf("offBits:%d\n", offBits);
    
    //位图信息头40个字节
    int biSize = d.parseInt();
    printf("biSize:%d\n", biSize);
    
    int biWidth = d.parseInt();
    printf("biWidth:%d\n", biWidth);
    int biHeight = d.parseInt();
    printf("biHeight:%d\n", biHeight);
    
    //值总为1
    short biPlanes = d.parseShort();
    printf("biPlanes:%d\n", biPlanes);
    
    short biBitCount = d.parseShort();
    printf("biBitCount:%d\n", biPlanes);
    
    //值一般0表示不压缩
    int biCompression = d.parseInt();
    printf("biCompression:%d\n", biCompression);
    
    int biSizeImage = d.parseInt();
    printf("biSizeImage:%d\n", biSizeImage);
    
    int biXPelsPerMerter = d.parseInt();
    printf("biXPelsPerMerter:%d\n", biXPelsPerMerter);
    
    int biYPelsPerMerter = d.parseInt();
    printf("biYPelsPerMerter:%d\n", biYPelsPerMerter);
    
    int biClrUsed= d.parseInt();
    printf("biClrUsed:%d\n", biClrUsed);
    
    int biClrImportant = d.parseInt();
    printf("biClrImportant:%d\n", biClrImportant);
    
    //读取位图图片数据
    d.setPos(0);
    d.skip(offBits);
    char *biImageData = d.parseChars(biSizeImage);
}
