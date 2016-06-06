//
//  server.hpp
//  CG
//
//  Created by 鲁飞 on 16/6/6.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef server_hpp
#define server_hpp

#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <wchar.h>

void connectServer();

void sendMsg(char *msg, int size);

void* communicateWithServer(void *arg);//与服务器通信

void getMsg(char *buf, int size);//本地获得缓存中数据

bool checkMsg();/*检查是否有消息*/

#endif /* server_hpp */
