#pragma once
#include <iostream>
#include "Piece.h"
#include "../Board.h"
#include "../../Helper/Helper.h"

using namespace std;

class Pawn : public Piece{
    void prepareMoves(Board& board) {
        if(color == Color::WHITE){
            if(Helper::isEmptySquare(board, position.first, position.second + 1)){
                moves.push_back({position.first, position.second + 1});
            }

            if(Helper::haveOpponentPiece(board, color, position.first + 1, position.second + 1)){
                moves.push_back({position.first + 1, position.second + 1});
            }

            if(Helper::haveOpponentPiece(board, color, position.first - 1, position.second + 1)){
                moves.push_back({position.first - 1, position.second + 1});
            }
        }
    }
};