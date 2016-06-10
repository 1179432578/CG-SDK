//
//  Gobang.hpp
//  CG
//
//  Created by lewis on 16/6/5.
//  Copyright © 2016年 lewis. All rights reserved.
//

#ifndef Gobang_hpp
#define Gobang_hpp

#include <stdio.h>
#include "mgl.h"
#include "Node.h"

/*五子棋对战游戏*/

void initGame();

void drawCheckerboard(int size);

void drawPiece(int x, int y);

void mouse(int button, int state, int x, int y);

void keyboard(unsigned char keyValue, int x, int y);

bool checkWin(int arr[][12], int x, int y);

void drawOtherPiece(int x, int y);

/*处理从服务器接收的数据*/
void handleRev(char *buf);

/*每帧的逻辑处理*/
void logicHandle(float delta);

class Scene : public Node{
public:
    void click(Event *e){printf("123 123 123\n");};
};
#endif /* Gobang_hpp */