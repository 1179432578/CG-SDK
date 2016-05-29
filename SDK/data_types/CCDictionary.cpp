//
//  CCDictonary.cpp
//  LImage
//
//  Created by lewis on 16/4/26.
//  Copyright © 2016年 lewis. All rights reserved.
//

#include "CCDictionary.h"

CCObject* CCDictionary::objectForKey(char *key){
    return m_dictionary->get(key);
}

CCObject* CCDictionary::objectForKey(int key){
    return m_dictionary->get(key);
}

void CCDictionary::setObject(CCObject* pObject, char *key){
    m_dictionary->put(key, pObject);
}

void CCDictionary::setObject(CCObject* pObject, int key){
    m_dictionary->put(key, pObject);
}

void CCDictionary::removeObjectForKey(char *key){
    
}

void CCDictionary::removeObjectForKey(int key){

}