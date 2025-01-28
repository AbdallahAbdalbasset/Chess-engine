#pragma once
#include "Piece.h"

class Board;
class Knight : public Piece {
    public:
    void prepareMoves(Board&);
};

