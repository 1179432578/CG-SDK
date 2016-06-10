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
    
    bool isFileExistX(const std::string& strFilePath);
    
    bool isFileExist(const std::string& strFilePath);/*不支持搜索路径 use it in command program*/
    
    std::string getWritablePathX();/*获得可写路径*/
    
    std::string getWritablePath();/*获得可写路径 use it in command program*/
    
    void addSearchPath(const char* path_);/*添加搜索路径*/
    
    std::string getFullPathForFilename(const std::string& filename, const std::string& searchDirctory);/*根据文件名与搜索目录获得文件的绝对路径*/
    
    std::string getFullPathForFilename(const char* pszFileName);/*根据文件名获得文件的绝对路径*/
    
    unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);/*获得磁盘文件数据，支持搜索路径*/
    
    /*addsearch writetofile*/
private:
    std::vector<std::string> m_searchDirectoryArray;/*搜索目录带斜杠的*/
};

#endif /* FileUtils_hpp */
