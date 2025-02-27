
#include "../Headers/Rook.h"
#include "../../Board.h"
#include "../../../Helper/Helper.h"


Rook::Rook(){
    moves.reserve(maxPieceMoves);
}
void Rook::prepareMoves(Board& board){
    moves.clear();
    int i = position.first;
    int j = position.second;
    
    // Left
    while(Helper::isEmptySquare(board, i-1, j)){
        moves.push_back({--i, j});
    }
    if(Helper::isInBoard(i-1, j)){
        moves.push_back({--i, j});
    }
    
    // Right
    i = position.first;
    j = position.second;
    while(Helper::isEmptySquare(board, i+1, j)){
        moves.push_back({++i, j});
    }
    if(Helper::isInBoard(i+1, j)){
        moves.push_back({++i, j});
    }

    // Down
    i = position.first;
    j = position.second;
    while(Helper::isEmptySquare(board, i, j-1)){
        moves.push_back({i, --j});
    }
    if(Helper::isInBoard(i, j-1)){
        moves.push_back({i, --j});
    }

    // Up
    i = position.first;
    j = position.second;
    while(Helper::isEmptySquare(board, i, j+1)){
        moves.push_back({i, ++j});
    }
    if(Helper::isInBoard(i, j+1)){
        moves.push_back({i, ++j});
    }
}

int Rook::getValue(){
    if(color == Color::WHITE) return (value + pst[(7-position.second)*8+position.first]);
    return (value + pst[position.second*8+position.first]);
}