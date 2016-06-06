//
//  Client.hpp
//  server
//
//  Created by lewis on 16/6/6.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef Client_hpp
#define Client_hpp

#include <stdio.h>
#include <netinet/in.h>
//#include <sys/socket.h>

/*
 *客户端
 *每与一个客户端建立连接就创建一个Client记录信息，每与一个客户端建立连接就删除一个Client
 */
class Client{
public:
    struct sockaddr_in address;
    int socket;
    Client *m_next;
public:
    void description();/*输出Client的信息*/
};

/*客户管理*/
class ClientManager{
    friend class Client;/*为了直接访问Client*/
public:
    static ClientManager* getInstance();
    void addClient(Client *client);
    void removeClient(Client *client);
    void sendMessage(Client *client, char *buf,  int size);/*把client的信息转发给其它客户端*/
//    Client *m_head = NULL;
};



#endif /* Client_hpp */
