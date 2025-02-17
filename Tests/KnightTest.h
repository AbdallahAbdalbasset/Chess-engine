#pragma once
#include "../Board/Pieces/Headers/Knight.h"
#include "../Board/Board.h"
#include "../Helper/enum.h"
#include <iostream>

class KnightTest {
    public:
    void runAllTests(){
        twoMoves();
        emptyBoard();
        opponentPieceUpRight();

        cout<<"Knight tests done"<<endl;
    }

    void twoMoves();
    void emptyBoard();
    void opponentPieceUpRight();
};

void KnightTest::twoMoves(){
    Board board;
    Knight knight;
    knight.position = {0, 0};
    knight.color = Color::WHITE;

    board.board[1][2] = Helper::createKnight(Color::WHITE, {1, 2});
    board.board[2][1] = Helper::createKnight(Color::WHITE, {2, 1});
    knight.prepareMoves(board);

    vector<pair<int, int> > correctMoves;
    correctMoves.push_back({1, 2});
    correctMoves.push_back({2, 1});

    sort(correctMoves.begin(), correctMoves.end());
    sort(knight.moves.begin(), knight.moves.end());

    assert(knight.moves == correctMoves);
}

void KnightTest::emptyBoard(){
    Board board;
    Knight knight;
    knight.position = {3, 3};
    knight.color = Color::WHITE;

    knight.prepareMoves(board);

    vector<pair<int, int> > correctMoves;
    correctMoves.push_back({4, 5});
    correctMoves.push_back({5, 4});
    correctMoves.push_back({2, 5});
    correctMoves.push_back({5, 2});
    correctMoves.push_back({2, 1});
    correctMoves.push_back({1, 2});
    correctMoves.push_back({1, 4});
    correctMoves.push_back({4, 1});

    sort(correctMoves.begin(), correctMoves.end());
    sort(knight.moves.begin(), knight.moves.end());

    assert(knight.moves == correctMoves);
}

void KnightTest::opponentPieceUpRight(){
    Board board;
    Knight knight;
    knight.position = {3, 3};
    knight.color = Color::WHITE;

    board.board[4][5] = Helper::createKnight(Color::BLACK, {4, 5});

    knight.prepareMoves(board);

    vector<pair<int, int> > correctMoves;
    correctMoves.push_back({4, 5});
    correctMoves.push_back({5, 4});
    correctMoves.push_back({2, 5});
    correctMoves.push_back({5, 2});
    correctMoves.push_back({2, 1});
    correctMoves.push_back({1, 2});
    correctMoves.push_back({1, 4});
    correctMoves.push_back({4, 1});

    sort(correctMoves.begin(), correctMoves.end());
    sort(knight.moves.begin(), knight.moves.end());

    assert(knight.moves == correctMoves);
}