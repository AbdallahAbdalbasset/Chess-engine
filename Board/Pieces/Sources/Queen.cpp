#pragma once
#include  "../Headers/Queen.h"
#include "../../Board.h"
#include "../../../Helper/Helper.h"
#include "Rook.cpp"
#include "Bishop.cpp"

void Queen::prepareMoves(Board& board){
    Rook rook;
    Bishop bishop;
    
    rook.position = position;
    bishop.position = position;
    rook.color = color;
    bishop.color = color;

    rook.prepareMoves(board);
    bishop.prepareMoves(board);

    for(auto move : rook.moves)
        moves.push_back(move);
    for(auto move : bishop.moves)
        moves.push_back(move);
}