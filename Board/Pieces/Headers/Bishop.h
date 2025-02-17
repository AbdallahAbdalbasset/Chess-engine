#pragma once
#include "Piece.h"

class Board;
class Bishop : public Piece {
   public:
   vector<int> pst =  {
		-2,-1,-1,-1,-1,-1,-1,-2,
		-1, 0, 0, 0, 0, 0, 0,-1,
		-1, 0, 1, 2, 2, 1, 0,-1,
		-1, 2, 2, 2, 2, 1, 1,-1,
		-1, 0, 2, 2, 2, 2, 0,-1,
		-1, 2, 2, 1, 1, 2, 2,-1,
		-1, 2, 0, 0, 0, 0, 2,-1,
		-2,-1,-1,-1,-1,-2,-1,-2,
	};
   void prepareMoves(Board&);
   int getValue();
};

