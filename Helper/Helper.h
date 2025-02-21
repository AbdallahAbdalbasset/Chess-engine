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
    static void playMove(Board& board, Color, pair<int, int> from, pair<int, int> to, shared_ptr<Piece> curPiece, shared_ptr<Piece> targetPiece);
    static void unPlayMove(Board& board, Color, pair<int, int> from, pair<int, int> to, shared_ptr<Piece> curPiece, shared_ptr<Piece> targetPiece, vector<bool>& casleData);
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
    static void generateMoves(Board board, Color color, vector<pair<int, pair<pair<int, int>, pair<int, int>>>>&, int&, int, int, bool);
    static void kingSideCasle(Board& board, Color color);
    static void kingSideUncasle(Board& board, Color color);
    static void queenSideCasle(Board& board, Color color);
    static void queenSideUncasle(Board& board, Color color);
    static pair<pair<int, int>, pair<int, int>> decodeMove(string move);
    static bool isThisMoveACheck(Board board, Color color, pair<int, int> from, pair<int, int> to, pair<int, int> kingPosition);
    static bool isBishopOrQueenAttackKing(Board board, Color color, pair<int, int> kingPosition);
    static bool isRookOrQueenAttackKing(Board board, Color color, pair<int, int> kingPosition);
    static bool isKnightAttackKing(Board board, Color color, pair<int, int> kingPosition);
    static bool isPawnAttackKing(Board board, Color color, pair<int, int> kingPosition);

};

