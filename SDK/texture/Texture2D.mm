//
//  Texture2D.cpp
//  CG
//
//  Created by lewis on 16/6/10.
//  Copyright © 2016年 lewis. All rights reserved.
//

#import "Texture2D.h"
#import <Cocoa/Cocoa.h>
#include <string.h>


Texture2D* Texture2D::create(int x, int y, const char *filename){
    Texture2D *ret = new Texture2D;
    ret->m_posX = x;
    ret->m_posY = y;
    
    std::string newFilename = FileUtils::getInstance()->getFullPathForFilename(filename);
    
    /*读取图片数据*/
    NSImage *img = [[NSImage alloc]initWithContentsOfFile:[[NSString alloc] initWithUTF8String:newFilename.c_str()]];
    NSRect rt = NSMakeRect(0, 0, img.size.width , img.size.height);
    CGImageRef temImg = [img CGImageForProposedRect:&rt context:nil hints:nil];
    CGDataProviderRef pr = CGImageGetDataProvider(temImg);
    CFDataRef r = CGDataProviderCopyData(pr);
    ret->m_data = (unsigned char*)CFDataGetBytePtr(r);
    ret->m_height = CGImageGetHeight(temImg);
    ret->m_width = CGImageGetWidth(temImg);
    
    return ret;
}

extern int *FBO;
extern int WIDTH, HEIGHT;
void Texture2D::draw(){
    unsigned char pixel[4];
    unsigned char pixel2[4];
    for (int h=0; h<m_height-1; h++) {
        for (int w=0; w<m_width-1; w++) {
            memcpy(pixel, m_data + 4*(h*m_width + w), 4);
            memcpy(pixel2, FBO + (m_posY+h)*WIDTH + m_posX+w, 4);
//            pixel[0] = pixel[0] + pixel[3];
//            pixel[3] = pixel[0] - pixel[3];
//            pixel[0] = pixel[0] - pixel[3];
//            unsigned tmp = pixel[0];
//            pixel[0] = pixel[3];
//            pixel[3] = tmp;
            
//            FBO[(m_posY+h)*WIDTH + m_posX+w] = pixel;
            if (pixel[3] == 0) {
                continue;/*不透明度*/
            }
            
            /*alpha blend*/
            /*source*/
            float alpha = 0.3f;
            pixel[0] *= alpha;
            pixel[1] *= alpha;
            pixel[2] *= alpha;
            
            /*destination*/
            float alpha2= 0.7f;
            pixel2[0] *= alpha2;
            pixel2[1] *= alpha2;
            pixel2[2] *= alpha2;
            
            /*finally*/
            pixel[0] += pixel2[0];
            pixel[1] += pixel2[0];
            pixel[2] += pixel2[0];

            
            memcpy(FBO + (m_posY+h)*WIDTH + m_posX+w, pixel, 4);
        }
    }
}