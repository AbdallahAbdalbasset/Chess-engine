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
    static void playMove(Board& board, pair<int, int> from, pair<int, int> to, shared_ptr<Piece> curPiece, shared_ptr<Piece> targetPiece);
    static bool isValidMove(Board board, pair<int, int> to, Color color);
    static shared_ptr<Piece> createPawn(Color color, pair<int, int> position);
    static shared_ptr<Piece> createRook(Color color, pair<int, int> position);
    static shared_ptr<Piece> createKnight(Color color, pair<int, int> position);
    static shared_ptr<Piece> createBishop(Color color, pair<int, int> position);
    static shared_ptr<Piece> createQueen(Color color, pair<int, int> position);
    static shared_ptr<Piece> createKing(Color color, pair<int, int> position);
    static Board copyBoard(Board board);
    static bool isDraw(Board& board);
    static bool isStalemate(vector<pair<pair<int, int>, pair<pair<int, int>, int>>> moves);
    static void generateMoves(Board board, Color color, vector<pair<int, pair<pair<int, int>, pair<int, int>>>>&, int&, int);
};

