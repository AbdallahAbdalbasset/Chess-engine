#pragma once
#include "Piece.h"

class Board;
class Queen : public Piece {
    public:
    vector<int> pst {
		-2,-1,-1,-1,-1,-1,-1,-2,
		-1, 0, 0, 0, 0, 0, 0,-1,
		-1, 0, 1, 1, 1, 1, 0,-1,
		-5, 0, 1, 1, 1, 1, 1,-1,
		 0, 0, 1, 1, 1, 1, 1,-1,
		-1, 2, 1, 1, 1, 2, 2,-1,
		-1, 0, 1, 0, 0, 0, 0,-1,
		-2,-1,-1,-1,-1,-1,-1,-2
	};
    void prepareMoves(Board&);
    int getValue();
};

