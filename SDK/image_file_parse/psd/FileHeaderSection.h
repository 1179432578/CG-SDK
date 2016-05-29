//
//  FileHeaderSection.h
//  CG
//
//  Created by 鲁飞 on 16/5/24.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef FileHeaderSection_h
#define FileHeaderSection_h
#include "MutableData.h"

struct FileHeaderSection{
    //    4
    //Signature: always equal to '8BPS' . Do not try to read the file if the signature does not match this value.
    char Signature[4];
    
    //    2
    //Version: always equal to 1. Do not try to read the file if the version does not match this value. (**PSB** version is 2.)
    short Version;
    
    //    6
    //Reserved: must be zero.
    char Reserved[6];
    
    //    2
    //    The number of channels in the image, including any alpha channels. Supported range is 1 to 56.
    short numberOfChannels;
    
    //    4
    //    The height of the image in pixels. Supported range is 1 to 30,000.
    //    (**PSB** max of 300,000.)
    int heightOfImage;
    
    //    4
    //    The width of the image in pixels. Supported range is 1 to 30,000.
    //    (*PSB** max of 300,000)
    int widthOfImage;
    
    //    2
    //Depth: the number of bits per channel. Supported values are 1, 8, 16 and 32
    short numberOfBitsPerChannerl;
    
    //    2
    //    The color mode of the file. Supported values are: Bitmap = 0; Grayscale = 1; Indexed = 2; RGB = 3; CMYK = 4; Multichannel = 7; Duotone = 8; Lab = 9.
    //http://zhidao.baidu.com/link?url=SqWFEDaY5CLvnCKTYVXBJCQh2C8jhj2oX2ejWJHbyR1f_GLa8nB9x1aNWfxueXQ6333bA2ZbotauL42trHv_Ha
    short colorModeOfFile;
};

void paserFileHeaderSection(FileHeaderSection *fhs, MutableData *md);

#endif /* FileHeaderSection_h */
