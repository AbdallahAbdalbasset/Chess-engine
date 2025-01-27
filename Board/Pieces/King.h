#pragma once
#include <iostream>
#include "Piece.h"
#include "../Board.h"
#include "../../Helper/Helper.h"

class King : public Piece {
    public:
    void prepareMoves(Board&);
};

void King::prepareMoves(Board& board){

    for(int i = position.first - 1;i <= position.first + 1; i++){
        for(int j = position.second - 1; j <= position.second + 1; j++){
            if(i==position.first&&j==position.second) continue;
            if(Helper::isInBoard(i, j) && (Helper::isEmptySquare(board, i, j) || Helper::haveOpponentPiece(board, color, i, j))) { 
                moves.push_back({i, j});
            }
        }
    }  
}