
#include "../Headers/Pawn.h"
#include "../../Board.h"
#include "../../../Helper/Helper.h"


Pawn::Pawn(){
    moves.reserve(maxPieceMoves);
}
void Pawn::prepareMoves(Board& board){
    moves.clear();
    int increment = (color == Color::WHITE) ? 1 : -1;

    // Forward move
    if(Helper::isInBoard(position.first , position.second + increment)&&
        Helper::isEmptySquare(board, position.first, position.second + increment)){
        moves.push_back({position.first, position.second + increment});
        
        // First move
        if(Helper::isInBoard(position.first, position.second + 2*increment)&&
        (position.second == ((color == Color::WHITE) ? 1 : 6)) && Helper::isEmptySquare(board, position.first, position.second + 2*increment)){
            moves.push_back({position.first, position.second + 2*increment});
        }
    }
    // Takes a piece
    if(Helper::isInBoard(position.first + 1, position.second + increment)&&
    !Helper::isEmptySquare(board, position.first + 1, position.second + increment)){
        moves.push_back({position.first + 1, position.second + increment});
    }
    // Takes a piece
    if(Helper::isInBoard(position.first - 1, position.second + increment)&&
    !Helper::isEmptySquare(board, position.first - 1, position.second + increment)){
        moves.push_back({position.first - 1, position.second + increment});
    }

    
}

int Pawn::getValue(){
    if(color == Color::WHITE) return (value + pst[(7-position.second)*8+position.first]);
    return (value + pst[position.second*8+position.first]);
}