#pragma once

#include "../Headers/King.h"
#include "../../Board.h"
#include "../../../Helper/Helper.h"

void King::prepareMoves(Board& board){
    moves.clear();
    for(int i = position.first - 1;i <= position.first + 1; i++){
        for(int j = position.second - 1; j <= position.second + 1; j++){
            if(i==position.first&&j==position.second) continue;
            if(!Helper::isInBoard(i, j)) continue;
            
            moves.push_back({i, j});
        }
    }  
}