//
//  ImageResourcesSection.cpp
//  CG
//
//  Created by 鲁飞 on 16/5/24.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "ImageResourcesSection.h"

void pasreImageResourcesSection(ImageResourcesSection *irs, MutableData *md){
    irs->lengthOfImageResourceScetion = md->parseInt();
    printf("irs->lengthOfImageResourceScetion: %d\n", irs->lengthOfImageResourceScetion);
    
    md->skip(irs->lengthOfImageResourceScetion);
    
    
    //暂不解析这些内容
    //    //Image Resource Blocks  111
    //    char imageResourceBlockSignature[4];
    //    m_data->parseChars(imageResourceBlockSignature, 4);
    //    printChar(imageResourceBlockSignature, 4, "imageResourceBlockSignature");
    //
    //    short resourceId = m_data->parseShort();
    //    printf("resourceId: %d\n", resourceId);
    //
    //    short size = m_data->parseShort();
    //    printf("size:%d\n", size);
    //
    //    int resourceDataSize = m_data->parseInt();
    //    printf("resourceDataSize:%d\n", resourceDataSize);
    //
    //    m_data->skip(resourceDataSize+1);//这个必须加一 不合理
    //
    //    //Image Resource Blocks  22222222222222
    //    char imageResourceBlockSignature2[4];
    //    m_data->parseChars(imageResourceBlockSignature2, 4);
    //    printChar(imageResourceBlockSignature2, 4, "imageResourceBlockSignature");
    //
    //    short resourceId2 = m_data->parseShort();
    //    printf("resourceId: %d\n", resourceId2);
    //
    //    short size2 = m_data->parseShort();
    //    printf("size:%d\n", size2);
    //
    //    int resourceDataSize2 = m_data->parseInt();
    //    printf("resourceDataSize:%d\n", resourceDataSize2);
    //
    //    m_data->skip(resourceDataSize2);
    //
    //    //Image Resource Blocks  3333333333
    //    char imageResourceBlockSignature3[4];
    //    m_data->parseChars(imageResourceBlockSignature3, 4);
    //    printChar(imageResourceBlockSignature3, 4, "imageResourceBlockSignature3");
    //
    //    short resourceId3 = m_data->parseShort();
    //    printf("resourceId: %d\n", resourceId3);
    //
    //    short size3 = m_data->parseShort();
    //    printf("size:%d\n", size3);
    //
    //    int resourceDataSize3 = m_data->parseInt();
    //    printf("resourceDataSize:%d\n", resourceDataSize3);
    //
    //    m_data->skip(resourceDataSize3);
    //
    //    //4444444444
    //    char imageResourceBlockSignature4[4];
    //    m_data->parseChars(imageResourceBlockSignature4, 4);
    //    printChar(imageResourceBlockSignature4, 4, "imageResourceBlockSignature3");

}

