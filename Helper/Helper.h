#pragma once
#include  "../Board/Board.h"
#include "enum.h"

class Helper{
    public:
    static bool isInBoard(int i, int j);
    static bool isEmptySquare(Board& board, int i, int j);
    static bool haveOpponentPiece(Board& board, Color color, int i, int j);
};

bool Helper::isInBoard(int i, int j){
    return (i>=0 && i<8 && j>=0 && j<8);
}

bool Helper::isEmptySquare(Board& board, int i, int j){
    if(!isInBoard(i, j)) return false;
    return board.board[i][j] == nullptr;
}

bool Helper::haveOpponentPiece(Board& board, Color color, int i, int j){
    if(!isInBoard(i, j) || isEmptySquare(board, i, j)) return false;
    return board.board[i][j]->color != color;
}