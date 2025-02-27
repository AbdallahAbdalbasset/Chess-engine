#pragma once
#include "../Board/Pieces/Headers/King.h"
#include "../Board/Board.h"
#include "../Helper/enum.h"
#include <iostream>

class KingTest {
    public:
    void runAllTests(){
        threeMoves();
        emptyBoard();
        opponentPieceUpRight();

        cout<<"King tests done"<<endl;
    }

    void threeMoves();
    void emptyBoard();
    void opponentPieceUpRight();
};

void KingTest::threeMoves(){
    Board board;
    King king;
    king.position = {0, 0};
    king.color = Color::WHITE;
    
    board.board[1][1] = Helper::createKnight(Color::WHITE, {1, 1});
    board.board[0][1] = Helper::createKnight(Color::WHITE, {0, 1});
    board.board[1][0] = Helper::createKnight(Color::WHITE, {1, 0});
    king.prepareMoves(board);

    vector<pair<int, int> > correctMoves;
    correctMoves.push_back({1, 1});
    correctMoves.push_back({0, 1});
    correctMoves.push_back({1, 0});

    sort(correctMoves.begin(), correctMoves.end());
    sort(king.moves.begin(), king.moves.end());

    assert(king.moves == correctMoves);
}


void KingTest::emptyBoard(){
    Board board;
    King king;
    king.position = {3, 3};
    king.color = Color::WHITE;

    king.prepareMoves(board);

    vector<pair<int, int> > correctMoves;
    correctMoves.push_back({2, 2});
    correctMoves.push_back({2, 3});
    correctMoves.push_back({2, 4});
    correctMoves.push_back({3, 2});
    correctMoves.push_back({3, 4});
    correctMoves.push_back({4, 2});
    correctMoves.push_back({4, 3});
    correctMoves.push_back({4, 4});

    sort(correctMoves.begin(), correctMoves.end());
    sort(king.moves.begin(), king.moves.end());

    assert(king.moves == correctMoves);
}


void KingTest::opponentPieceUpRight(){
    Board board;
    King king;
    king.position = {3, 3};
    king.color = Color::WHITE;
    
    board.board[4][4] = Helper::createKnight(Color::WHITE, {4, 4});
    
    king.prepareMoves(board);

    vector<pair<int, int> > correctMoves;
    correctMoves.push_back({2, 2});
    correctMoves.push_back({2, 3});
    correctMoves.push_back({2, 4});
    correctMoves.push_back({3, 2});
    correctMoves.push_back({3, 4});
    correctMoves.push_back({4, 2});
    correctMoves.push_back({4, 3});
    correctMoves.push_back({4, 4});

    sort(correctMoves.begin(), correctMoves.end());
    sort(king.moves.begin(), king.moves.end());

    assert(king.moves == correctMoves);
}