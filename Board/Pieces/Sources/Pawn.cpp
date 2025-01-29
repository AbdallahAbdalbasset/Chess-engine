#pragma once
#include "../Headers/Pawn.h"
#include "../../Board.h"
#include "../../../Helper/Helper.h"

void Pawn::prepareMoves(Board& board){
    moves.clear();
    int increment = (color == Color::WHITE) ? 1 : -1;
        
    // Forward move
    if(Helper::isEmptySquare(board, position.first, position.second + increment)){
        moves.push_back({position.first, position.second + increment});
    }
    // Takes a piece
    if(Helper::haveOpponentPiece(board, color, position.first + 1, position.second + increment)){
        moves.push_back({position.first + 1, position.second + increment});
    }
    // Takes a piece
    if(Helper::haveOpponentPiece(board, color, position.first - 1, position.second + increment)){
        moves.push_back({position.first - 1, position.second + increment});
    }
}