#pragma once
#include "../Board/Pieces/Headers/Bishop.h"
#include "../Board/Board.h"
#include "../Helper/enum.h"
#include <iostream>

class BishopTest {
    public:
    void runAllTests(){
        twoMoves();
        emptyBoard();
        opponentPieceUpRight();

        cout<<"Bishop tests done"<<endl;
    }

    void twoMoves();
    void emptyBoard();
    void opponentPieceUpRight();

};

void BishopTest::twoMoves(){
    Board board;
    Bishop bishop;
    bishop.position = {2, 0};
    bishop.color = Color::WHITE;

    board.board[1][1] = Helper::createBishop(Color::WHITE, {1, 1});
    board.board[3][1] = Helper::createBishop(Color::WHITE, {3, 1});
    bishop.prepareMoves(board);

    vector<pair<int, int> > correctMoves;
    correctMoves.push_back({1, 1});
    correctMoves.push_back({3, 1});

    sort(correctMoves.begin(), correctMoves.end());
    sort(bishop.moves.begin(), bishop.moves.end());

    assert(bishop.moves == correctMoves);
}

void BishopTest::emptyBoard(){
    Board board;
    Bishop bishop;
    bishop.position = {5, 5};
    bishop.color = Color::WHITE;
    bishop.prepareMoves(board);

    vector<pair<int, int> > correctMoves;
    int i = 5;
    int j = 5;
    while(i + 1 < 8 && j + 1 < 8){
        correctMoves.push_back({++i, ++j});
    }

    i = 5;
    j = 5;
    while(i - 1 >= 0 && j - 1 >= 0){
        correctMoves.push_back({--i, --j});
    }

    i = 5;
    j = 5;
    while(i + 1 < 8 && j - 1 >= 0){
        correctMoves.push_back({++i, --j});
    }

    i = 5;
    j = 5;
    while(i - 1 >= 0 && j + 1 < 8){
        correctMoves.push_back({--i, ++j});
    }

    sort(correctMoves.begin(), correctMoves.end());
    sort(bishop.moves.begin(), bishop.moves.end());

    assert(bishop.moves == correctMoves);

}


void BishopTest::opponentPieceUpRight(){
    Board board;
    Bishop bishop;
    bishop.position = {5, 5};
    bishop.color = Color::WHITE;

    board.board[6][6] = Helper::createBishop(Color::BLACK, {6, 6});
    bishop.prepareMoves(board);

    vector<pair<int, int> > correctMoves;
    correctMoves.push_back({6, 6});

    int i = 5;
    int j = 5;
    while(i - 1 >= 0 && j - 1 >= 0){
        correctMoves.push_back({--i, --j});
    }

    i = 5;
    j = 5;
    while(i + 1 < 8 && j - 1 >= 0){
        correctMoves.push_back({++i, --j});
    }

    i = 5;
    j = 5;
    while(i - 1 >= 0 && j + 1 < 8){
        correctMoves.push_back({--i, ++j});
    }

    sort(correctMoves.begin(), correctMoves.end());
    sort(bishop.moves.begin(), bishop.moves.end());

    assert(bishop.moves == correctMoves);
}