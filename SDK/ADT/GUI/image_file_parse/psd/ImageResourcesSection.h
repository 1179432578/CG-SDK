//
//  ImageResourcesSection.hpp
//  CG
//
//  Created by 鲁飞 on 16/5/24.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef ImageResourcesSection_hpp
#define ImageResourcesSection_hpp

#include <stdio.h>
#include "MutableData.h"

struct ImageResourceBlocks{
    //    4
    //    Signature: '8BIM'
    char Signature[4];
    
    //    2
    //    Unique identifier for the resource. Image resource IDs contains a list of resource IDs used by Photoshop.
    short imageResourceId;
    
    //    Variable
    //    Name: Pascal string, padded to make the size even (a null name consists of two bytes of 0)
    char imageResourceNameLength; //a null name consists of two bytes of 0 所以长度为0是要skip 2
    char *imageResourceName;
    
    //    4
    //    Actual size of resource data that follows
    int sizeOfResourceData;
    
    //    Variable
    //    The resource data, described in the sections on the individual resource types. It is padded to make the size even.
    //资源数据，暂时不解析，直接跳过
};

// Image resources are used to store non-pixel data associated with images, such as pen tool paths
struct ImageResourcesSection{
    //    4
    //    Length of image resource section. The length may be zero.
    int lengthOfImageResourceScetion;
    
    //    Variable
    //    Image resources (Image Resource Blocks ).
    ImageResourceBlocks imageResBlos;
};

void pasreImageResourcesSection(ImageResourcesSection *irs, MutableData *md);

#endif /* ImageResourcesSection_hpp */
