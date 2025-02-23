#pragma once
#include <iostream>
#include "Pieces/Headers/Piece.h"
using namespace std;

class Board{
    public:
    const int boardSize = 8;
    bool whiteKingSideCasle = true; // means the king and rook did not moved
    bool whiteQueenSideCasle = true; // means the king and rook did not moved
    bool blackKingSideCasle = true; // means the king and rook did not moved
    bool blackQueenSideCasle = true; // means the king and rook did not moved
    vector<vector<shared_ptr<Piece>> > board;
    vector<vector<pair<int, int> > > lastMove;

    Board();
    void initializeBoard();
    void printBoard();
    void prepareMoves();
    bool canKingSideCasle(Color);
    bool canQueenSideCasle(Color);
    void reprepareMoves(pair<int, int> from, pair<int, int> to);
    void calcMovesThatToucheThePosition(Board& board, pair<int, int> point);
};

