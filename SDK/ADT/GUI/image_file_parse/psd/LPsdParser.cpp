//
//  LPsdParser.cpp
//  CG
//
//  Created by 鲁飞 on 16/5/24.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "LPsdParser.h"

//psd格式说明
//http://www.adobe.com/devnet-apps/photoshop/fileformatashtml/#50577409_46269

void LPsdParser::read(const char *filename){
    m_data = new MutableData;
    
    //把磁盘文件读入内存中
    m_data->readFile(filename);
//    m_data->printHexadecimal();
    
    //parse File Header section
    paserFileHeaderSection(&m_fhs, m_data);
    
    //parse Color Mode Data Section
    parseColorModeDataSection(&m_cmds, m_data);
    
    //parse Image Resource Section
    pasreImageResourcesSection(&m_irs, m_data);
    
    //parse Layer and Mask Information Section
//    readLayerAndMaskInformationSection();
    parseLayerAndMaskInformationSection(&m_lamis, m_data);
}

void LPsdParser::readLayerAndMaskInformationSection(){
    m_layerAndMaskInformationSectionLength = m_data->parseInt();
    printf("m_layerAndMaskInformationSectionLength: %d\n", m_layerAndMaskInformationSectionLength);
    
    /*--------------------------------Layer info--------------------------------*/
    int length = m_data->parseInt();//4
    short layerCount = m_data->parseShort();//2
    printf("length:%d layerCount:%d\n", length, layerCount);
    
    //4*4 Rectangle containing the contents of the layer. Specified as top, left, bottom, right coordinates
    int top = m_data->parseInt();//4
    int left = m_data->parseInt();//4
    int bottom = m_data->parseInt();//4
    int right = m_data->parseInt();//4
    printf("top:%d left:%d bottom:%d right:%d\n", top, left, bottom, right);
    
    //2 Number of channels in the layer
    short channels = m_data->parseShort();
    printf("channes: %d\n", channels);
    
    //6 * number of channels
    for (int i=0; i<channels; i++) {
        short channelId = m_data->parseShort();
        int channelDataLength = m_data->parseInt();
        printf("channelId: %d channelDataLength: %d\n", channelId, channelDataLength);
    }
    
    //4 Blend mode signature: '8BIM'
    char blendModeSignature[4];
    m_data->parseChars(blendModeSignature, 4);
    printf("blendModeSignature: %4.4s\n", blendModeSignature);
    
    //4 Blend mode key:
    char blendModeKey[4];
    m_data->parseChars(blendModeKey, 4);
    printf("blendModeKey: %4.4s\n", blendModeKey);
    
    //1 Opacity. 0 = transparent ... 255 = opaque
    BYTE opacity;
    m_data->parseChar(&opacity);
    printf("opacity: %d\n", opacity);
    
    //1 Clipping: 0 = base, 1 = non-base
    BYTE Clipping;
    m_data->parseChar(&Clipping);
    printf("Clipping: %d\n", Clipping);
    
//    1
//    Flags:
//    bit 0 = transparency protected;
//    bit 1 = visible;
//    bit 2 = obsolete;
//    bit 3 = 1 for Photoshop 5.0 and later, tells if bit 4 has useful information;
//    bit 4 = pixel data irrelevant to appearance of document
    BYTE Flags;
    m_data->parseChar(&Flags);
    printf("Flags: %d\n", Flags);
    
//    1
//    Filler (zero)
    BYTE Filler;
    m_data->parseChar(&Filler);
    printf("Filler: %d\n", Filler);
    
//    4
//    Length of the extra data field ( = the total length of the next five fields).
    int extraDataFieldLength = m_data->parseInt();
     printf("Length of the extra data field: %d\n", extraDataFieldLength);
    
//    Variable
//    Layer mask data: See See Layer mask / adjustment layer data for structure. Can be 40 bytes, 24 bytes, or 4 bytes if no layer mask.
//    4
//    Size of the data: Check the size and flags to determine what is or is not present. If zero, the following fields are not present
    int dataSize = m_data->parseInt();
    printf("Size of the data: %d\n", dataSize);
    
    if (dataSize == 0) {
        //If zero, the following fields are not present
    }
    else{
    
    }
    
//    Variable
//    Layer blending ranges: See See Layer blending ranges data.
//    4
//    Length of layer blending ranges data
    int layerBlendRangeDataLebgth = m_data->parseInt();
    printf("layerBlendRangeDataLebgth: %d\n", layerBlendRangeDataLebgth);
    
//    4
//    Composite gray blend source. Contains 2 black values followed by 2 white values. Present but irrelevant for Lab & Grayscale.
    int grayBlendSource = m_data->parseInt();
    printf("grayBlendSource: %d\n", grayBlendSource);
//    4
//    Composite gray blend destination range
    int compositeGrayBlendDestination = m_data->parseInt();
    printf("grayBlendSource: %d\n", compositeGrayBlendDestination);
    
//    4
//    First channel source range
    
    
//    4
//    First channel destination range
    
//    4
//    Second channel source range
//    4
//    Second channel destination range
    int n = (layerBlendRangeDataLebgth - 8) / 4;
    for (int i = 0; i < n; i++) {
        //channel source range
        int channelSourceRange = m_data->parseInt();
        printf("channelSourceRange: %d\n", channelSourceRange);
        
        //channel destination range
//        int channelDestinationRange = m_data->parseInt();
//        printf("channelSourceRange: %d channelDestinationRange: %d\n", channelSourceRange, channelDestinationRange);
    }
    
//    Layer records
//    Variable
//    Layer name: Pascal string, padded to a multiple of 4 bytes.
    char layerNameLength;
    m_data->parseChar(&layerNameLength);
    printf("layerNameLength: %d\n", layerNameLength);
    
    char name[100];
    memset(name, 0, 100);
    m_data->parseChars(name, layerNameLength);
    printf("layerName: %s\n", name);
    
    m_data->skip(extraDataFieldLength - 4 - 44 - 1 - 14);
    int t = m_data->parseInt();
    int l = m_data->parseInt();
    int b = m_data->parseInt();
    int r = m_data->parseInt();
    printf("%d %d %d %d\n", t, l, b, r);
    
    short chns = m_data->parseShort();
    printf("chns: %d\n", chns);
    
//    Variable
//    Channel image data. Contains one or more image data records (see See Channel image data for structure) for each layer. The layers are in the same order as in the layer information (previous row of this table).
//    2
//    Compression. 0 = Raw Data, 1 = RLE compressed, 2 = ZIP without prediction, 3 = ZIP with prediction.
//    short compression = m_data->parseShort();
//    printf("compression: %d\n", compression);
    
}

void testPsdParser(){
    LPsdParser *psd = new LPsdParser;
//    psd->read("/Users/lufei1/Desktop/computer graphics-SDK/SDK/resource/dress主角(完成).psd");
    psd->read("/Users/lewis/Desktop/CG-SDK-master/SDK/resource/dress up整理（完成）.psd");
    
}