//
//  FileUtils.hpp
//  CG
//
//  Created by lewis on 16/6/7.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef FileUtils_hpp
#define FileUtils_hpp

#include <stdio.h>
#include "CCDictionary.h"
#include <vector> /*即将实现stl*/
#include <string>

/*文件操作 读/写*/
class FileUtils{
public:
    static FileUtils* getInstance();
    
    bool isFileExist(const std::string& strFilePath);
    
    std::string getWritablePath();/*获得可写路径*/
    
    std::string fullPathForFilename(const char* pszFileName);/*获得文件全路径，通过搜索路径拼接给定路径查找文件*/
    
    unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);/*获得磁盘文件数据*/
    
    /*addsearch writetofile*/
private:
    std::vector<std::string> m_searchPathArray;
};

#endif /* FileUtils_hpp */
