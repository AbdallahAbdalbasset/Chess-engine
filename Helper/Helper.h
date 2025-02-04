#pragma once
#include  "../Board/Board.h"
#include "../Board/Pieces/Headers/Piece.h"
#include "enum.h"

class Helper{
    public:
    static bool isInBoard(int i, int j);
    static bool isEmptySquare(Board& board, int i, int j);
    static bool haveOpponentPiece(Board& board, Color color, int i, int j);
    static bool isCheck(Board& board,Color color);
    static bool isCheckMate(Board board, Color color);
    static void playMove(Board& board, pair<int, int> from, pair<int, int> to, Piece* curPiece, Piece* targetPiece);
    static bool isValidMove(Board board, pair<int, int> to, Color color);
    static Piece* createPawn(Color color, pair<int, int> position);
    static Piece* createRook(Color color, pair<int, int> position);
    static Piece* createKnight(Color color, pair<int, int> position);
    static Piece* createBishop(Color color, pair<int, int> position);
    static Piece* createQueen(Color color, pair<int, int> position);
    static Piece* createKing(Color color, pair<int, int> position);
    
};

