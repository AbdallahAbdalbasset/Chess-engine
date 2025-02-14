# pragma once
#include <iostream>
#include"../Helper/enum.h"
using namespace std;

class Board;
class Engine{
    public:
    static int maxDepth;
    static int threadsCount;
    static pair<pair<int,int>,pair<pair<int,int>,int>> getMove(Board board, Color color);
    static pair<pair<int,int>,pair<pair<int,int>,int>> search(Board board,Color color,int depth, int alpha, int beta, int threadId);
    static void prepareThreadMoves(int threadId, Board board, Color color, pair<pair<int, int>, pair<pair<int, int>, int>>& move);
    static int getScore(Board&);
};