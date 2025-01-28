#pragma once
#include "../Headers/Rook.h"
#include "../../Board.h"
#include "../../../Helper/Helper.h"

void Rook::prepareMoves(Board& board){
    int i = position.first;
    int j = position.second;
    
    // Left
    while(Helper::isEmptySquare(board, i-1, j)){
        moves.push_back({--i, j});
    }
    if(Helper::haveOpponentPiece(board, color, i-1, j)){
        moves.push_back({--i, j});
    }
    
    // Right
    i = position.first;
    j = position.second;
    while(Helper::isEmptySquare(board, i+1, j)){
        moves.push_back({++i, j});
    }
    if(Helper::haveOpponentPiece(board, color, i+1, j)){
        moves.push_back({++i, j});
    }

    // Down
    i = position.first;
    j = position.second;
    while(Helper::isEmptySquare(board, i, j-1)){
        moves.push_back({i, --j});
    }
    if(Helper::haveOpponentPiece(board, color, i, j-1)){
        moves.push_back({i, --j});
    }

    // Up
    i = position.first;
    j = position.second;
    while(Helper::isEmptySquare(board, i, j+1)){
        moves.push_back({i, ++j});
    }
    if(Helper::haveOpponentPiece(board, color, i, j+1)){
        moves.push_back({i, ++j});
    }
}