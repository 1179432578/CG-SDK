//
//  LayerAndMaskInformationSection.hpp
//  CG
//
//  Created by 鲁飞 on 16/5/24.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef LayerAndMaskInformationSection_hpp
#define LayerAndMaskInformationSection_hpp

#include <stdio.h>
#include "MutableData.h"

struct ChannelImageData{
//    2
//    Compression. 0 = Raw Data, 1 = RLE compressed, 2 = ZIP without prediction, 3 = ZIP with prediction.
    short compression;
    
//    Variable
//    Image data.
//    If the compression code is 0, the image data is just the raw image data, whose size is calculated as (LayerBottom-LayerTop)* (LayerRight-LayerLeft) (from the first field in See Layer records).
//    If the compression code is 1, the image data starts with the byte counts for all the scan lines in the channel (LayerBottom-LayerTop) , with each count stored as a two-byte value.(**PSB** each count stored as a four-byte value.) The RLE compressed data follows, with each scan line compressed separately. The RLE compression is the same compression algorithm used by the Macintosh ROM routine PackBits, and the TIFF standard.
//        If the layer's size, and therefore the data, is odd, a pad byte will be inserted at the end of the row.
//        If the layer is an adjustment layer, the channel data is undefined (probably all white.)
    char *imageData;
    
};

struct LayerBlendingRangesData{
//    4
//    Length of layer blending ranges data
    int lengthOfLayerBlendingRangesData;
//    4
//    Composite gray blend source. Contains 2 black values followed by 2 white values. Present but irrelevant for Lab & Grayscale.
    int compositeGrayBlendSource;
    
//    4
//    Composite gray blend destination range
    int compositeGrayBlendDestinationRange;
//    4
//    First channel source range
//    4
//    First channel destination range
//    4
//    Second channel source range
//    4
//    Second channel destination range
//    ...
//    ...
//    4
//    Nth channel source range
//    4
//    Nth channel destination range
    int *channelSourceRange;
    int *channelDestinationRange;
};

struct LayerMaskAdjustLayerData{
//    4
//    Size of the data: Check the size and flags to determine what is or is not present. If zero, the following fields are not present
    int sizeOfData;
    
//    4 * 4
//    Rectangle enclosing layer mask: Top, left, bottom, right
    
//    1
//    Default color. 0 or 255
   
//    1
//    Flags.
//    bit 0 = position relative to layer
//    bit 1 = layer mask disabled
//    bit 2 = invert layer mask when blending (Obsolete)
//    bit 3 = indicates that the user mask actually came from rendering other data
//    bit 4 = indicates that the user and/or vector masks have parameters applied to them
    
//    1
//    Mask Parameters. Only present if bit 4 of Flags set above.
//    Variable
//    Mask Parameters bit flags present as follows:
//    bit 0 = user mask density, 1 byte
//    bit 1 = user mask feather, 8 byte, double
//    bit 2 = vector mask density, 1 byte
//    bit 3 = vector mask feather, 8 bytes, double
    
//    2
//    Padding. Only present if size = 20. Otherwise the following is present
    
//    1
//    Real Flags. Same as Flags information above.
  
//    1
//    Real user mask background. 0 or 255.
   
//    4 * 4
//    Rectangle enclosing layer mask: Top, left, bottom, right.
};

struct LayerRecord{
//    4 * 4
//    Rectangle containing the contents of the layer. Specified as top, left, bottom, right coordinates
    int topOfLayer, leftOfLayer, bottomOfLayer, rightOfLayer;
    
//    2
//    Number of channels in the layer
    short numberOfChannel;
    
//    6 *
//    number of channels
//    Channel information. Six bytes per channel, consisting of:
//    2 bytes for Channel ID: 0 = red, 1 = green, etc.;
//    -1 = transparency mask; -2 = user supplied layer mask, -3 real user supplied layer mask (when both a user mask and a vector mask are present)
//    4 bytes for length of corresponding channel data. (**PSB** 8 bytes for length of corresponding channel data.) See See Channel image data for structure of channel data.
    short *channelId;
    int *lengthOfChannelData;
//    4
//    Blend mode signature: '8BIM'
    char blendModeSignature[4];
    
//    4
//    Blend mode key:
//    'pass' = pass through, 'norm' = normal, 'diss' = dissolve, 'dark' = darken, 'mul ' = multiply, 'idiv' = color burn, 'lbrn' = linear burn, 'dkCl' = darker color, 'lite' = lighten, 'scrn' = screen, 'div ' = color dodge, 'lddg' = linear dodge, 'lgCl' = lighter color, 'over' = overlay, 'sLit' = soft light, 'hLit' = hard light, 'vLit' = vivid light, 'lLit' = linear light, 'pLit' = pin light, 'hMix' = hard mix, 'diff' = difference, 'smud' = exclusion, 'fsub' = subtract, 'fdiv' = divide 'hue ' = hue, 'sat ' = saturation, 'colr' = color, 'lum ' = luminosity,
    char blendModeKey[4];
   
//    1
//    Opacity. 0 = transparent ... 255 = opaque
    char opacity;
    
//    1
//    Clipping: 0 = base, 1 = non-base
    char clipping;
    
//    1
//    Flags:
//    bit 0 = transparency protected;
//    bit 1 = visible;
//    bit 2 = obsolete;
//    bit 3 = 1 for Photoshop 5.0 and later, tells if bit 4 has useful information;
//    bit 4 = pixel data irrelevant to appearance of document
    char flag;
    
//    1
//    Filler (zero)
    char filler;
    
//    4
//    Length of the extra data field ( = the total length of the next five fields).
    int lengthOfExtraDataField;
   
//    Variable
//    Layer mask data: See See Layer mask / adjustment layer data for structure. Can be 40 bytes, 24 bytes, or 4 bytes if no layer mask.
    LayerMaskAdjustLayerData layerMaskAdjustLayerData;
    
//    Variable
//    Layer blending ranges: See See Layer blending ranges data.
    LayerBlendingRangesData layerBlendingRange;
    
//    Variable
//    Layer name: Pascal string, padded to a multiple of 4 bytes.
    char layerNameLength;
    char *layerName;
};

struct LayerInfo{
//    4
//    Length of the layers info section, rounded up to a multiple of 2. (**PSB** length is 8 bytes.)
    int lengthOfLayerInfoSection;
    
//    2
//    Layer count. If it is a negative number, its absolute value is the number of layers and the first alpha channel contains the transparency data for the merged result.
    short layerCount;
    
//    Variable
//    Information about each layer. See Layer records describes the structure of this information for each layer.
    LayerRecord *layerRecord;
    
//    Variable
//    Channel image data. Contains one or more image data records (see See Channel image data for structure) for each layer. The layers are in the same order as in the layer information (previous row of this table).
    
};

struct LayerAndMaskInformationSection{
//    4
//    Length of the layer and mask information section. (**PSB** length is 8 bytes.)
    int lengthOfLayerAndMaskInformationSection;
    
//    Variable
//    Layer info (see See Layer info for details).
    LayerInfo layerInfo;
//    Variable
//    Global layer mask info (see See Global layer mask info for details).
    
//    Variable
//    (Photoshop 4.0 and later)
//    Series of tagged blocks containing various types of data. See See Additional Layer Information for the list of the types of data that can be included here.
};

void parseLayerAndMaskInformationSection(LayerAndMaskInformationSection *layerAndMaskInfo, MutableData *md);

#endif /* LayerAndMaskInformationSection_hpp */
