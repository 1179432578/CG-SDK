//
//  FileUtils.cpp
//  CG
//
//  Created by lewis on 16/6/7.
//  Copyright © 2016年 lewis. All rights reserved.
//

#import "FileUtils.h"
#import <Foundation/Foundation.h>
#import <unistd.h>

FileUtils* FileUtils::getInstance(){
    static FileUtils* s_sharedFileUtils = NULL;
    
    if (!s_sharedFileUtils) {
        s_sharedFileUtils = new FileUtils;
    }
    
    return s_sharedFileUtils;
}

static NSFileManager* s_fileManager = [NSFileManager defaultManager];

bool FileUtils::isFileExistX(const std::string& strFilePath){
    if (0 == strFilePath.length())
    {
        return false;
    }
    
    bool bRet = false;
    
    if (strFilePath[0] != '/')
    {
        std::string path;
        std::string file;
        size_t pos = strFilePath.find_last_of("/");
        if (pos != std::string::npos)
        {
            file = strFilePath.substr(pos+1);
            path = strFilePath.substr(0, pos+1);
        }
        else
        {
            file = strFilePath;
        }
        
        /*返回全路径，递归查找
         *在包目录下查找 fullpath=包路径/path/file
         */
        NSString* fullpath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:file.c_str()]
                                                             ofType:nil
                                                        inDirectory:[NSString stringWithUTF8String:path.c_str()]];
        if (fullpath != nil) {
            bRet = true;
        }
 
        /*
         *获得可执行文件的目录
         *"/Users/lewis/Library/Developer/Xcode/DerivedData/CG-cnvdmvxebezswoffbdvwuiqulwnn/Build/Products/Debug"
         *NSString *p =  [[NSBundle mainBundle] bundlePath];
         */
        
    }
    else
    {
        // Search path is an absolute path.
        if ([s_fileManager fileExistsAtPath:[NSString stringWithUTF8String:strFilePath.c_str()]]) {
            bRet = true;
        }
    }
    
    return bRet;
}

/*
 *判断文件是否存在
 *http://www.cnblogs.com/lancidie/archive/2011/06/30/2094924.html
 */
bool FileUtils::isFileExist(const std::string& strFilePath){
    /*获得工作目录
    char buf[1024];
    getcwd(buf, 1024);
    printf("%s\n", buf);*/
    
    /*检查文件存在性, 这个只有工作目录是包含可执行文件目录，才对相对路径的文件判断有效
    if (access(strFilePath.c_str(), 0) != -1) {
        return true;
    }*/
    if (0 == strFilePath.length()) {
        return false;
    }
    
    if (strFilePath[0] != '/') {/**/
        std::string path;
        std::string file;
        size_t pos = strFilePath.find_last_of("/");
        if (pos != std::string::npos)/*有斜杠把文件路径分成路径名与文件名*/
        {
            file = strFilePath.substr(pos+1);
            path = strFilePath.substr(0, pos+1);
        }
        else
        {
            file = strFilePath;
        }
        
        NSString* fullpath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:file.c_str()]
                                                             ofType:nil
                                                        inDirectory:[NSString stringWithUTF8String:path.c_str()]];
        if (fullpath != nil) {
            return true;
        }
    }
    else{/*绝对路径，可以使用NSFileManager的fileExistsAtPath判断*/
        if (access(strFilePath.c_str(), 0) != -1) {
            return true;
        }
    }
    
    
    return false;
}

std::string FileUtils::getWritablePathX()
{
    // save to document folder
    /*mac os:/Users/lewis/Library/Caches*/
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
    
    /*ios os*/
    //NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    
    NSString *documentsDirectory = [paths objectAtIndex:0];
    std::string strRet = [documentsDirectory UTF8String];
    strRet.append("/");
    return strRet;
}


std::string FileUtils::getWritablePath(){
    NSString *p =  [[NSBundle mainBundle] bundlePath];/*包路径：可执行文件的包含目录路径*/
    
    return [p UTF8String];
}

void FileUtils::addSearchPath(const char* path_)
{
    std::string strPrefix;
    std::string path(path_);
    /*ios mac没有前缀，就是在包目录下查找，android是有的*/
//    if (!isAbsolutePath(path))
//    { // Not an absolute path
//        strPrefix = m_strDefaultResRootPath;
//    }
    path = strPrefix + path;
    if (path.length() > 0 && path[path.length()-1] != '/')
    {
        path += "/";/*加了斜杠就是目录了，而不是路径了*/
    }
    m_searchDirectoryArray.push_back(path);
}

std::string FileUtils::getFullPathForFilename(const std::string& filename, const std::string& searchPath){
    std::string file = filename;
    std::string file_path = "";
    size_t pos = filename.find_last_of("/");
    if (pos != std::string::npos)/*分割路径与文件名*/
    {
        file_path = filename.substr(0, pos+1);
        file = filename.substr(pos+1);
    }
    
    std::string path = searchPath;/*searchPath带斜杠的，应该是目录*/
    path += file_path;
    
    std::string ret;
    if (path[0] != '/')/*相对目录*/
    {
        NSString* fullpath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:file.c_str()]
                                                             ofType:nil
                                                        inDirectory:[NSString stringWithUTF8String:path.c_str()]];
        if (fullpath != nil) {
            ret =  [fullpath UTF8String];
        }
    }
    else/*绝对目录*/
    {
        std::string fullPath = path + file;
        // Search path is an absolute path.
        if ([s_fileManager fileExistsAtPath:[NSString stringWithUTF8String:fullPath.c_str()]]) {
            ret =  fullPath;
        }
    }
    
    return ret;
}

std::string FileUtils::getFullPathForFilename(const char* pszFileName)
{
//    CCAssert(pszFileName != NULL, "CCFileUtils: Invalid path");
    
    std::string strFileName = pszFileName;
    if (pszFileName[0] == '/')
    {
        return pszFileName;
    }
    
    std::string fullpath = "";
    for (std::vector<std::string>::iterator iter = m_searchDirectoryArray.begin();
         iter != m_searchDirectoryArray.end(); ++iter) {
            fullpath = getFullPathForFilename(pszFileName, *iter);
            
            if (fullpath.length() > 0)
            {
                return fullpath;
            }
    }
    
    return pszFileName;
}

unsigned char* FileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{
    unsigned char * pBuffer = NULL;
//    CCAssert(pszFileName != NULL && pSize != NULL && pszMode != NULL, "Invalid parameters.");
    *pSize = 0;
    do
    {
        /*从磁盘读数据*/
        std::string fullPath = getFullPathForFilename(pszFileName);
        FILE *fp = fopen(fullPath.c_str(), pszMode);
//        CC_BREAK_IF(!fp);
        
        fseek(fp,0,SEEK_END);
        *pSize = ftell(fp);
        fseek(fp,0,SEEK_SET);
        pBuffer = new unsigned char[*pSize];
        *pSize = fread(pBuffer, sizeof(unsigned char), *pSize, fp);
        fclose(fp);
    } while (0);
    
    if (!pBuffer)
    {
        std::string msg = "Get data from file(";
        msg.append(pszFileName).append(") failed!");
        printf("%s\n", msg.c_str());
    }
    
    return pBuffer;
}