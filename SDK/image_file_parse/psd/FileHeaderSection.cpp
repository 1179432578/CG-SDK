//
//  FileHeaderSection.cpp
//  CG
//
//  Created by 鲁飞 on 16/5/24.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include <stdio.h>
#include "FileHeaderSection.h"

void paserFileHeaderSection(FileHeaderSection *fhs, MutableData *md){
    md->parseChars(fhs->Signature, 4);
    printf("fhs->Signature: %4.4s\n", fhs->Signature);
    
    fhs->Version = md->parseShort();
    printf("fhs->Version: %d\n", fhs->Version);
    
    md->parseChars(fhs->Reserved, 6);
    printf("fhs->Reserved: %6.6s\n", fhs->Reserved);
    
    fhs->numberOfChannels = md->parseShort();
    printf("fhs->numberOfChannels: %d\n", fhs->numberOfChannels);
    
    fhs->heightOfImage = md->parseInt();
    printf("fhs->heightOfImage: %d\n", fhs->heightOfImage);
    
    fhs->widthOfImage = md->parseInt();
    printf("fhs->widthOfImage: %d\n", fhs->widthOfImage);
    
    fhs->numberOfBitsPerChannerl = md->parseShort();
    printf("fhs->numberOfBitsPerChannerl: %d\n", fhs->numberOfBitsPerChannerl);
    
    fhs->colorModeOfFile = md->parseShort();
    printf("fhs->colorModeOfFile: %d\n", fhs->colorModeOfFile);

}