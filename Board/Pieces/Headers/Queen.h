#pragma once
#include "Piece.h"

class Board;
class Queen : public Piece {
    public:
    void prepareMoves(Board&);
};

