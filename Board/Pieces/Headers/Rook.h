#pragma once
#include "Piece.h"

class Baord;
class Rook : public Piece{
    public:
	Rook();
    vector<int> pst =  {
		0, 0, 0, 0, 0, 0, 0, 0,
		5,10,10,10,10,10,10, 5,
	   -5, 0, 0, 0, 0, 0, 0,-5,
	   -5, 0, 0, 0, 0, 0, 0,-5,
	   -5, 0, 0, 0, 0, 0, 0,-5,
	   -5, 0, 0, 0, 0, 0, 0,-5,
	   -5, 0, 0, 0, 0, 0, 0,-5,
	    0,-1, -1, 2, 2,-1,-1, 0
	};
    void prepareMoves(Board&);
    int getValue();
};

