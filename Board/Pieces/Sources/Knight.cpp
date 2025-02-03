
#include "../Headers/Knight.h"
#include "../../Board.h"
#include "../../../Helper/Helper.h"

void Knight::prepareMoves(Board& board){
    moves.clear();
    int i = position.first;
    int j = position.second;

    // Up-right
    if(Helper::isInBoard(i-2, j+1)) { 
        moves.push_back({i-2, j+1});
    }
    
    // Up-left
    if(Helper::isInBoard(i-2, j-1)) { 
        moves.push_back({i-2, j-1});
    }
    
    // Down-right
    if(Helper::isInBoard(i+2, j+1)) { 
        moves.push_back({i+2, j+1});
    }
    
    // Down-left
    if(Helper::isInBoard(i+2, j-1)) { 
        moves.push_back({i+2, j-1});
    }
    
    // Right-up
    if(Helper::isInBoard(i-1, j+2)) { 
        moves.push_back({i-1, j+2});
    }
    
    // Right-down
    if(Helper::isInBoard(i+1, j+2)) { 
        moves.push_back({i+1, j+2});
    }
    
    // Left-up
    if(Helper::isInBoard(i-1, j-2)) { 
        moves.push_back({i-1, j-2});
    }
    
    // Left-down
    if(Helper::isInBoard(i+1, j-2)) { 
        moves.push_back({i+1, j-2});
    }
}