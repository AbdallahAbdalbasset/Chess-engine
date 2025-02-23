#pragma once
#include "Piece.h"

class Board;
class Knight : public Piece {
    public:
	Knight();
    vector<int> pst = {
		-5,-4,-3,-3,-3,-3,-4,-5,
		-4, 4, 4, 4, 4, 4, 4,-4,
		-3, 4, 4, 4, 4, 4, 4,-3,
		-3, 1, 3, 4, 4, 3, 1,-3,
		-3, 0, 3, 4, 4, 3, 0,-3,
		-3, 1, 2, 3, 3, 1, 1,-3,
		-4,-2, 0, 1, 1, 0,-2,-4,
		-5,-3,-1,-3,-3,-3,-10,-5,
	};
    void prepareMoves(Board&);
    int getValue();
};

