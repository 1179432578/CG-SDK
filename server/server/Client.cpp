//
//  Client.cpp
//  server
//
//  Created by lewis on 16/6/6.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "Client.h"

static Client *m_head = NULL;//bug

void Client::description(){

}

ClientManager* ClientManager::getInstance(){
    static ClientManager *ret = NULL;
    
    if (!ret) {
        ret = new ClientManager;
        return ret;
    }
    
    return NULL;
}

void ClientManager::addClient(Client *client){
    client->m_next = m_head;
    m_head = client;
}

void ClientManager::removeClient(Client *client){
    Client *p = m_head;
    Client *pre = NULL;
    
    while (p) {
        if (p == client) {
            if (pre) {
                pre->m_next = p->m_next;
                delete p;
            }
            else{
                m_head = p->m_next;
                delete p;
            }
            
            break;
        }
        
        pre = p;
        p = p->m_next;
    }
}

void ClientManager::sendMessage(Client *client, char *buf, int size){
    Client *p = m_head;
    while (p) {
        if (p != client) {
            send(p->socket, buf, size, 0);
        }
        
        p = p->m_next;
    }
}
