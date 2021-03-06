//
//  server.cpp
//  CG
//
//  Created by 鲁飞 on 16/6/6.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "server.h"
#include <pthread.h>
#include <string.h>
#include "Gobang.h"
#include "text.h"

static int server_socket;
static char recvBuf[1024];/*用于接收消息*/
void connectServer(){
    struct sockaddr_in server_addr;
    server_addr.sin_len = sizeof(struct sockaddr_in);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(999999);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(&(server_addr.sin_zero),8);
    
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket error");
        return;
    }
    
    /*zero*/
    bzero(recvBuf, 1024);
    
    //connect 成功之后，系统将你创建的socket绑定到一个系统分配的端口上，且其为全相关，包含服务器端的信息，可以用来和服务器端进行通信。
    if (connect(server_socket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in))==0){
        /*发送ready*/
        send(server_socket, "ready", strlen("ready")+1, 0);
        
        /*接收OK*/
        recv(server_socket, recvBuf, 1024,0);
        printf("接收服务器%d消息:%s\n", server_socket, recvBuf);
        handleRev(recvBuf);
        
        /*启动一个线程接收数据*/
        pthread_t id;
        pthread_create(&id, NULL, keepServer, &server_socket);
        pthread_detach(id);
    }
}

void* keepServer(void *arg){
    int server_socket = *(int*)arg;
    
    /*进行循环处理*/
    while (true) {
        /*接收信息*/
        recv(server_socket, recvBuf, 1024, 0);
        handleRev(recvBuf);
    }

    return 0;
}

void sendMsg(char *msg, int size){
    send(server_socket, msg, size, 0);
}