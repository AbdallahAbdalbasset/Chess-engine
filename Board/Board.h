#pragma once
#include <iostream>
#include <vector>
#include "Pieces/Piece.h"

using namespace std;
class Board{
    public:
    const int boardSize = 8;
    vector<vector<Piece*> > board;
    vector<vector<pair<int, int> > > lastMove;

    Board():board(vector<vector<Piece*> >(8, vector<Piece*>(8, nullptr))){}
    void initializeBoard();
    void printBoard();
    void playMove();

};

void Board::initializeBoard(){}
void Board::playMove(){}
void Board::printBoard(){}