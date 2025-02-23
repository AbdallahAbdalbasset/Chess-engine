#pragma once
#include "Piece.h"

class Board;
class Queen : public Piece {
    public:
	Queen();
    vector<int> pst {
		-2,-1,-1,-1,-1,-1,-1,-2,
		-1, 1, 1, 1, 1, 1, 1,-1,
		-1, 1, 1, 1, 1, 1, 1,-1,
		-1, 1, 1, 1, 1, 1, 1,-1,
		-1, 1, 1, 1, 1, 1, 1,-1,
		-1, 2, 1, 1, 1, 3, 2,-1,
		-1, 0, 1, 0, 0, 0, 0,-1,
		-2,-1,-1,-2,-1,-1,-1,-2
	};
    void prepareMoves(Board&);
    int getValue();
};

