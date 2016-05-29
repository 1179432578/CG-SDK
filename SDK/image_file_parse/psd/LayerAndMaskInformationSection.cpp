//
//  LayerAndMaskInformationSection.cpp
//  CG
//
//  Created by 鲁飞 on 16/5/24.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "LayerAndMaskInformationSection.h"

void parseLayerAndMaskInformationSection(LayerAndMaskInformationSection *layerAndMaskInfo, MutableData *md){
    layerAndMaskInfo->lengthOfLayerAndMaskInformationSection = md->parseInt();
    printf("layerAndMaskInfo->lengthOfLayerAndMaskInformationSection: %d\n", layerAndMaskInfo->lengthOfLayerAndMaskInformationSection);
    
    /*--------------------------------Layer info start--------------------------------*/
    layerAndMaskInfo->layerInfo.lengthOfLayerInfoSection = md->parseInt();//4
    layerAndMaskInfo->layerInfo.layerCount = md->parseShort();//2
    short layerCount = layerAndMaskInfo->layerInfo.layerCount > 0 ? layerAndMaskInfo->layerInfo.layerCount : -layerAndMaskInfo->layerInfo.layerCount;
    printf("layerAndMaskInfo->lengthOfLayerInfoSection:%d\nlayerCount:%d\n", layerAndMaskInfo->layerInfo.lengthOfLayerInfoSection,
           layerCount);
    
    /*--------------------------------LayerRecord start--------------------------------*/
    //4*4 Rectangle containing the contents of the layer. Specified as top, left, bottom, right coordinates
    layerAndMaskInfo->layerInfo.layerRecord = new LayerRecord[layerCount];
    for (int i=0; i<layerCount; i++) {
        LayerRecord *layerRecord = &layerAndMaskInfo->layerInfo.layerRecord[i];
        layerRecord->topOfLayer = md->parseInt();//4
        layerRecord->leftOfLayer = md->parseInt();//4
        layerRecord->bottomOfLayer = md->parseInt();//4
        layerRecord->rightOfLayer = md->parseInt();//4
        printf("top:%d left:%d bottom:%d right:%d\n", layerRecord->topOfLayer, layerRecord->leftOfLayer,
               layerRecord->bottomOfLayer,layerRecord->rightOfLayer);
        
        //2 Number of channels in the layer
        layerRecord->numberOfChannel = md->parseShort();
        printf("layerRecord->numberOfChannel: %d\n", layerRecord->numberOfChannel);
        
        //6 * number of channels
        layerRecord->channelId = new short[layerRecord->numberOfChannel];
        layerRecord->lengthOfChannelData = new int[layerRecord->numberOfChannel];
        for (int i=0; i<layerRecord->numberOfChannel; i++) {
            layerRecord->channelId[i] = md->parseShort();
            layerRecord->lengthOfChannelData[i] = md->parseInt();
            printf("layerRecord->channelId: %d layerRecord->lengthOfChannelData: %d\n", layerRecord->channelId[i], layerRecord->lengthOfChannelData[i]);
        }
        
        //4 Blend mode signature: '8BIM'
        md->parseChars(layerRecord->blendModeSignature, 4);
        printf("layerRecord->blendModeSignature: %4.4s\n", layerRecord->blendModeSignature);
        
        //4 Blend mode key:
        md->parseChars(layerRecord->blendModeKey, 4);
        printf("layerRecord->blendModeKey: %4.4s\n", layerRecord->blendModeKey);
        
        //1 Opacity. 0 = transparent ... 255 = opaque
        md->parseChar(&layerRecord->opacity);
        printf("layerRecord->opacity: %d\n", layerRecord->opacity);
        
        //1 Clipping: 0 = base, 1 = non-base
        md->parseChar(&layerRecord->clipping);
        printf("layerRecord->clipping: %d\n", layerRecord->clipping);
        
        //    1
        //    Flags:
        //    bit 0 = transparency protected;
        //    bit 1 = visible;
        //    bit 2 = obsolete;
        //    bit 3 = 1 for Photoshop 5.0 and later, tells if bit 4 has useful information;
        //    bit 4 = pixel data irrelevant to appearance of document
        md->parseChar(&layerRecord->flag);
        printf("Flags: %d\n", layerRecord->flag);
        
        //    1
        //    Filler (zero)
        md->parseChar(&layerRecord->filler);
        printf("layerRecord->filler: %d\n", layerRecord->filler);
        
        //    4
        //    Length of the extra data field ( = the total length of the next five fields).
        layerRecord->lengthOfExtraDataField = md->parseInt();
        printf("layerRecord->lengthOfExtraDataField: %d\n", layerRecord->lengthOfExtraDataField);
        
        /*-----------------------------------LayerMaskAdjustLayerData start-----------------------------------*/
        //    Variable
        //    Layer mask data: See See Layer mask / adjustment layer data for structure. Can be 40 bytes, 24 bytes, or 4 bytes if no layer mask.
        //    4
        //    Size of the data: Check the size and flags to determine what is or is not present. If zero, the following fields are not present
        layerRecord->layerMaskAdjustLayerData.sizeOfData = md->parseInt();
        printf("layerRecord->layerMaskAdjustLayerData.sizeOfData: %d\n", layerRecord->layerMaskAdjustLayerData.sizeOfData);
        
        if (layerRecord->layerMaskAdjustLayerData.sizeOfData == 0) {
            //If zero, the following fields are not present
        }
        else{
            
        }
        /*-----------------------------------LayerMaskAdjustLayerData end-----------------------------------*/
        
        
        /*-----------------------------------LayerBlendingRangesData start-----------------------------------*/
        //    4
        //    Length of layer blending ranges data
        layerRecord->layerBlendingRange.lengthOfLayerBlendingRangesData = md->parseInt();
        printf("layerRecord->layerBlendingRange.lengthOfLayerBlendingRangesData: %d\n", layerRecord->layerBlendingRange.lengthOfLayerBlendingRangesData);
        
        //    4
        //    Composite gray blend source. Contains 2 black values followed by 2 white values. Present but irrelevant for Lab & Grayscale.
        layerRecord->layerBlendingRange.compositeGrayBlendSource = md->parseInt();
        printf("layerRecord->layerBlendingRange.compositeGrayBlendSource: %d\n", layerRecord->layerBlendingRange.compositeGrayBlendSource);
        //    4
        //    Composite gray blend destination range
        layerRecord->layerBlendingRange.compositeGrayBlendDestinationRange = md->parseInt();
        printf("layerRecord->layerBlendingRange.compositeGrayBlendDestinationRange: %d\n", layerRecord->layerBlendingRange.compositeGrayBlendDestinationRange);
        
        int n = (layerRecord->layerBlendingRange.lengthOfLayerBlendingRangesData - 8) / 8;
        layerRecord->layerBlendingRange.channelSourceRange = new int[n];
        layerRecord->layerBlendingRange.channelDestinationRange = new int[n];
        for (int i = 0; i < n; i++) {
            //channel source range
            layerRecord->layerBlendingRange.channelSourceRange[i] = md->parseInt();
            
            //channel destination range
            layerRecord->layerBlendingRange.channelDestinationRange[i] = md->parseInt();
            printf("layerRecord->layerBlendingRange.channelSourceRange: %d layerRecord->layerBlendingRange.channelDestinationRange: %d\n",
                   layerRecord->layerBlendingRange.channelSourceRange[i], layerRecord->layerBlendingRange.channelDestinationRange[i]);
        }
        
        /*-----------------------------------LayerBlendingRangesData end-----------------------------------*/
        
        //    Layer name: Pascal string, padded to a multiple of 4 bytes.
        md->parseChar(&layerRecord->layerNameLength);
        printf("layerRecord->layerNameLength: %d\n", layerRecord->layerNameLength);
        
        layerRecord->layerName = new char[layerRecord->layerNameLength];
        md->parseChars(layerRecord->layerName, layerRecord->layerNameLength);
        char *layerName = new char[layerRecord->layerNameLength+1];
        memset(layerName, 0, layerRecord->layerNameLength+1);
        strcpy(layerName, layerRecord->layerName);
        printf("layerRecord->layerName: %s\n", layerName);
        
        md->skip(layerRecord->lengthOfExtraDataField - 4 - 4 -
                 layerRecord->layerBlendingRange.lengthOfLayerBlendingRangesData
                 - 1 - layerRecord->layerNameLength);
    }
     /*--------------------------------LayerRecord end--------------------------------*/
    
    
    /*--------------------------------Channel image data start--------------------------------*/
    //    Variable
    //    Channel image data. Contains one or more image data records (see See Channel image data for structure) for each layer. The layers are in the same order as in the layer information (previous row of this table).
    //    2
    //    Compression. 0 = Raw Data, 1 = RLE compressed, 2 = ZIP without prediction, 3 = ZIP with prediction.
 
    for (int i=1; i<layerCount; i++) {
        
       
        //If the compression code is 0, the image data is just the raw image data, whose size is calculated as (LayerBottom-LayerTop)* (LayerRight-LayerLeft)
//        if (compression == 0) {
        
         LayerRecord *layerRecord = &layerAndMaskInfo->layerInfo.layerRecord[i];
        short compression = md->parseShort();
        printf("Channel image data compression: %d\n", compression);
        if (layerRecord->topOfLayer != 0) {
           
            
           
            int size = (layerRecord->bottomOfLayer - layerRecord->topOfLayer) * (layerRecord->rightOfLayer - layerRecord->leftOfLayer);
            printf("Channel image data size:%d\n", size);
//            printChar(layerRecord->layerName, layerRecord->layerNameLength, "layerRecord->layerName");
            
            md->skip(layerRecord->lengthOfChannelData[0] + layerRecord->lengthOfChannelData[1] +
                     layerRecord->lengthOfChannelData[2] + layerRecord->lengthOfChannelData[3]);

        }
//        }
        
    }
    
    int length = md->parseInt();
    printf("length: %d\n", length);
    short colorSpace = md->parseShort();
    printf("colorSpace: %d\n", colorSpace);
    short components[4];
    for (int i=0; i<4; i++) {
        components[i]  = md->parseShort();
        printf("components: %d\n", components[i]);
    }
    /*--------------------------------Channel image data end--------------------------------*/

}