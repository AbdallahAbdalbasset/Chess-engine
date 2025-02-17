#pragma once
#include "Piece.h"

class Board;
class Pawn : public Piece{
    public:
    vector<int> pst = {
		0, 0, 0, 0, 0, 0, 0, 0,
		6, 6, 6, 6, 6, 6, 6, 6,
		5, 5, 5, 5, 5, 5, 5, 5,
		4, 4, 4, 4, 4, 4, 4, 4,
		3, 3, 3, 3, 3, 2, 1, 1,
		2, 2, 2, 0, 0, 1, 2, 2,
		0, 0, 0,-2,-2, 2,-3, 0,
		0, 0, 0, 0, 0, 0, 0, 0
	};
    void prepareMoves(Board&);
    int getValue();
};

