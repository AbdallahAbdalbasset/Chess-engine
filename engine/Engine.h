# pragma once
#include <iostream>
#include"../Helper/enum.h"
using namespace std;

class Board;
class Engine{
    public:
    static const int maxDepth=4;
    static pair<pair<int,int>,pair<pair<int,int>,int>> getMove(Board board,Color color,int depth, int alpha, int beta);
    static int getScore(Board&);
};