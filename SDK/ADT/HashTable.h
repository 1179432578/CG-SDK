//
//  HashTable.hpp
//  LImage
//
//  Created by lewis on 16/4/23.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef HashTable_hpp
#define HashTable_hpp
#include <string.h>

class CCObject{
public:
//    CCObject(int n):m_n(n){}
//    int m_n;
};

//CCNull

typedef struct Entry{
    char * key;// key must be string
    
    CCObject *value; // value is subclass of CCObject
    
    int hash;
    
    struct Entry *next;
}Entry;

typedef struct Element{
    void *key;
    int size;//size of key
    void *value;
    struct Element *next;
}Element;

class HashTable {
public:
    HashTable();
    
    HashTable(int initialCapacity);
    
    HashTable(int initialCapacity, float loadFactor);
    
    // char*:CCObject pair
    void put(char *key, CCObject *value);
    CCObject* get(char *key);
    
    // int:CCObject pair
    void put(int key, CCObject *value);
    CCObject* get(int key);
    
    //base put
    void put(void *key, int size, void *value);
    
    //base get
    void* get(void *key, int size);
    
protected:
    int indexFor(int hash, int length);
    
private:
    // MUST POWER OF 2
    static const int DEFALUT_INITIAL_CAPACITY = 16;
    
    static const int MAXIMUM_CAPACITY = 1 << 30;
    
    static constexpr float DEFAULT_LOAD_FACTOR = 0.75f;
    
    /*----------------------------------------------*/
    //pointer of hashtable
    Element **m_table;
    
    //size of hashtable dataitem
    int m_size;
    
    int m_threshold;
    
    float m_loadFactor;
    
    float m_length;
};

#endif /* HashTable_hpp */
