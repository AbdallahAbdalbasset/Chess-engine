#pragma once
#include "Piece.h"

class Board;
class King : public Piece {
    public:
    void prepareMoves(Board&);
};

