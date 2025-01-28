#pragma once
#include "Piece.h"

class Board;
class Pawn : public Piece{
    public:
    void prepareMoves(Board&);
};

