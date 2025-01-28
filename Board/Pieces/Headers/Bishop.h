#pragma once
#include "Piece.h"

class Board;
class Bishop : public Piece {
   public:
   void prepareMoves(Board&);
};

