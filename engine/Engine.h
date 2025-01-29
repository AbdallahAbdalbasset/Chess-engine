# pragma once
#include <iostream>
#include"../Helper/enum.h"
using namespace std;

class Board;
class Engine{
    public:
    int depth=2;
    static pair<pair<int,int>,pair<pair<int,int>,int>> getMove(Board board ,Color color,int depth);
    static int getScore(Board &board);
};