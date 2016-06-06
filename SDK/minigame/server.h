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

void* keepServer(void *arg);//与服务器通信

#endif /* server_hpp */
