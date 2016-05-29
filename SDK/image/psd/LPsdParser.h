//
//  LPsdParser.hpp
//  CG
//
//  Created by 鲁飞 on 16/5/24.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef LPsdParser_hpp
#define LPsdParser_hpp

#include <stdio.h>
#include "MutableData.h"
#include "psdinclude.h"

#define PBYTE char*
#define BYTE char

/*psd解析类，实现对psd的读写、合并
 *
 *
 */
class LPsdParser{
public:
    //read operation
    void read(const char *filename);
    
    void readLayerAndMaskInformationSection();
    
    void readImageDataSection();
    //write operation
    
private:
    //读取磁盘文件
    MutableData *m_data;
    
    FileHeaderSection m_fhs;//File Header Section

    ColorModeDataSection m_cmds;//Color Mode Data Section

    ImageResourcesSection m_irs;//Image Resources Section
    
    LayerAndMaskInformationSection m_lamis;//Layer and Mask Information Section
    
    //Layer and Mask Information Section
    int m_layerAndMaskInformationSectionLength;//Length of the layer and mask information section. (**PSB** length is 8 bytes.)
};

void testPsdParser();


#endif /* LPsdParser_hpp */
