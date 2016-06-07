//
//  FileUtils.cpp
//  CG
//
//  Created by lewis on 16/6/7.
//  Copyright © 2016年 lewis. All rights reserved.
//

#import "FileUtils.h"
#import <Foundation/Foundation.h>

FileUtils* FileUtils::getInstance(){
    static FileUtils* s_sharedFileUtils = NULL;
    
    if (!s_sharedFileUtils) {
        s_sharedFileUtils = new FileUtils;
    }
    
    return s_sharedFileUtils;
}

static NSFileManager* s_fileManager = [NSFileManager defaultManager];

/*下面*/
bool FileUtils::isFileExist(const std::string& strFilePath){
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
        
        /*返回全路径，递归查找*/
        NSString* fullpath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:file.c_str()]
                                                             ofType:nil
                                                        inDirectory:[NSString stringWithUTF8String:path.c_str()]];
        if (fullpath != nil) {
            bRet = true;
        }
 
        /*
         *获得可执行文件的工作目录
         *"/Users/lewis/Library/Developer/Xcode/DerivedData/CG-cnvdmvxebezswoffbdvwuiqulwnn/Build/Products/Debug"
         */
        //NSString *p =  [[NSBundle mainBundle] bundlePath];

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

std::string FileUtils::getWritablePath()
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