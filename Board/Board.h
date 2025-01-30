#pragma once
#include <iostream>
#include "Pieces/Headers/Piece.h"
using namespace std;

class Board{
    public:
    const int boardSize = 8;
    vector<vector<Piece*> > board;
    vector<vector<pair<int, int> > > lastMove;

    Board();
    void initializeBoard();
    void printBoard();
    void prepareMoves();
};

