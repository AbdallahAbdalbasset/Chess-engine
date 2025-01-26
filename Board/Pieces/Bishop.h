#pragma once
#include <iostream>
#include "Piece.h"
#include "../Board.h"
#include "../../Helper/Helper.h"

class Bishop : public Piece {
    public:
    void prepareMoves(Board&);
};

void Bishop::prepareMoves(Board& board){

    int i = position.first;
    int j = position.second;

    // Up-right
    while(Helper::isEmptySquare(board, i+1, j+1)){
        moves.push_back({++i, ++j});
    }
    if(Helper::haveOpponentPiece(board, color, i+1, j+1)){
        moves.push_back({++i, ++j});
    }

    // Down-right
    i = position.first;
    j = position.second;
    while(Helper::isEmptySquare(board, i+1, j-1)){
        moves.push_back({++i, --j});
    }
    if(Helper::haveOpponentPiece(board, color, i+1, j-1)){
        moves.push_back({++i, --j});
    }

    // Up-left
    i = position.first;
    j = position.second;
    while(Helper::isEmptySquare(board, i-1, j+1)){
        moves.push_back({--i, ++j});
    }
    if(Helper::haveOpponentPiece(board, color, i-1, j+1)){
        moves.push_back({--i, ++j});
    }

    // Down-left
    i = position.first;
    j = position.second;
    while(Helper::isEmptySquare(board, i-1, j-1)){
        moves.push_back({--i, --j});
    }
    if(Helper::haveOpponentPiece(board, color, i-1, j-1)){
        moves.push_back({--i, --j});
    }
}