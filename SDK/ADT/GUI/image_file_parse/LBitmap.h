//
//  LBitmap.hpp
//  LImage
//
//  Created by lewis on 16/4/21.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef LBitmap_hpp
#define LBitmap_hpp

typedef struct tagBITMAPFILEHEADER
{
    short bfType;
    int bfSize;
    short bfReserved1;
    short bfReserved2;
    int bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
    int biSize;
    int biWidth;
    int biHeight;
    short biPlanes;
    short biBitCount;
    int biCompression;
    int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    int biClrUsed;
    int biClrImportant;
} BITMAPINFOHEADER;

//位图像素BGR(需要转为RGB), 每行字节数被4整除，不够4的倍数需要填充
//每个像素24位(BGR)，没使用调色板
class LBitmap{
public:
    void parseFromFile(char *bitmapName);
private:
    BITMAPFILEHEADER m_bitmapHeader;
    BITMAPINFOHEADER m_bitmapInfoHeader;
    char *m_buf;//位图图片数据
    int m_width;//位图宽
    int m_height;//位图高
};

#endif /* LBitmap_hpp */
