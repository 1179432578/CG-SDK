//
//  main.cpp
//  server
//
//  Created by 鲁飞 on 16/3/8.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include "Client.h"

/*与客户端进行通信*/
void* communicationWithClient(void *);
static int client_sockets[10];//
static int clientNum;//客户数

int main (int argc, const char * argv[])
{
    /*init*/
    clientNum = 0;
    
    //struct sockaddr_in : Socket address, internet style
    struct sockaddr_in server_addr;
    server_addr.sin_len = sizeof(struct sockaddr_in);
    server_addr.sin_family = AF_INET;//Address families AF_INET互联网地址簇
    server_addr.sin_port = htons(999999);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(&(server_addr.sin_zero),8);
    
    //创建socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);//SOCK_STREAM 有连接
    if (server_socket == -1) {
        perror("socket error");
        return 1;
    }
    
    //绑定socket：将创建的socket绑定到本地的IP地址和端口，此socket是半相关的，只是负责侦听客户端的连接请求，并不能用于和客户端通信
    int bind_result = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bind_result == -1) {
        perror("bind error");
        return 1;
    }
    
    //listen侦听 第一个参数是套接字，第二个参数为等待接受的连接的队列的大小，在connect请求过来的时候,
    //完成三次握手后先将连接放到这个队列中，直到被accept处理。如果这个队列满了，且有新的连接的时候，对方可能会收到出错信息。
    if (listen(server_socket, 5) == -1) {
        perror("listen error");
        return 1;
    }
    
    printf("对战平台服务器已启动\n");
    
    while (true) {
        //接受一个客户端的tcp连接 创建socket跟客户端通信
        //printf("wait client\n");
        
        struct sockaddr_in client_address;
        socklen_t address_len;
        
//        client_sockets[clientNum++] = accept(server_socket, (struct sockaddr *)&client_address, &address_len);
        int  client_socket = accept(server_socket, (struct sockaddr *)&client_address, &address_len);
        Client *c = new Client;
        c->socket = client_socket;
        ClientManager::getInstance()->addClient(c);
        setsockopt(client_socket, SOL_SOCKET, SO_NOSIGPIPE, NULL, sizeof(int));//防bug
        
        // 启动一个线程跟客户端进行通信
        pthread_t id;
        pthread_create(&id, NULL, communicationWithClient, c);
        //pthread_join(id, NULL);
        pthread_detach(id);
    }
    
    return 0;
}

void* communicationWithClient(void *arg){
//    int client_socket = *(int*)arg;
    Client *c = (Client*)arg;
    printf("客户id:%d\n", c->socket);
    
    char buf[1024];
    bzero(buf, 1024);
    //接收到ready
    recv(c->socket, buf, 1024, 0);
    printf("接收客户%d消息: %s\n", c->socket, buf);
    
    //发送OK
    char *str = "OK";
    send(c->socket, str, 3, 0);
    
    /*进行循环处理*/
    int revNum=1;
    while (revNum) {
        /*接收信息*/
        revNum = recv(c->socket, buf, 1024, 0);
        //printf("revnum: %d\n", revNum);
        if (revNum == 0) {/*如果没收到消息，结束通信*/
            printf("结束与客户%d的通信\n", c->socket);
            ClientManager::getInstance()->removeClient(c);
            break;
        }
        
        int cellX, cellY;
        memcpy(&cellX, buf, 4);
        memcpy(&cellY, buf+4, 4);
        printf("接收客户%d的消息:%d %d\n", c->socket, cellX, cellY);
        
        /*发送消息给另一个客户端*/
        ClientManager::getInstance()->sendMessage(c, buf, 8);
    }
    
    return 0;
}


