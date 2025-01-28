# pragma once
#include <iostream>
#include<vector>
#include"../../Helper/enum.h"
using namespace std;
class Board;
class Engine{
    public:
    int depth=2;
    Engine();
    static void getMove(Board &board ,Color color,int depth);
    static int getScore(Board &board);
};