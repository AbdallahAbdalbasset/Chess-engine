#pragma once
#include "../Board/Board.h"
#include "enum.h"

class Helper{
    public:

    // If this square is inside the board then return true
    static bool isInBoard(int i, int j){
        return (i>=0 && i<8 && j>=0 && j<8);
    }

    // If this square des not have a piece then return true 
    static bool isEmptySquare(Board& board, int i, int j){
        if(!isInBoard(i,j)) return false;
        return board.board[i][j] == nullptr;
    }

    static bool haveOpponentPiece(Board& board, Color color, int i, int j){
        if(isEmptySquare(borad, i, j)) return false;
        return board.board[i][j]->color != color;
    }
};