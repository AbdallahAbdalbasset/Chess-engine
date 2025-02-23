#include "../Headers/Queen.h"
#include "../../Board.h"
#include "../../../Helper/Helper.h"
#include "../Headers/Rook.h"
#include "../Headers/Bishop.h"


Queen::Queen(){
    moves.reserve(maxPieceMoves);
}
void Queen::prepareMoves(Board& board){
    moves.clear();
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

int Queen::getValue(){
    if(color == Color::WHITE) return (value + pst[(7-position.second)*8+position.first]);
    return (value + pst[position.second*8+position.first]);
}