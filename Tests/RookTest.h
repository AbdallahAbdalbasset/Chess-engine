#pragma once
#include "../Board/Pieces/Headers/Rook.h"
#include "../Board/Board.h"
#include "../Helper/enum.h"
#include <iostream>

class RookTest{
    public:
    void runAllTests(){
        twoMoves();
        emptyBoard();
        opponentPieceUp();

        cout<<"Rook tests done"<<endl;
    }

    void twoMoves();
    void emptyBoard();
    void opponentPieceUp();
};

void RookTest::twoMoves(){
    Board board;
    Rook rook;
    rook.position = {0, 0};
    rook.color = Color::WHITE;

    board.board[0][1] = Helper::createRook(Color::WHITE,  {0, 1});
    board.board[1][0] = Helper::createRook(Color::WHITE,  {1, 0});
    rook.prepareMoves(board);

    vector<pair<int, int>> correctMoves;
    correctMoves.push_back({0, 1});
    correctMoves.push_back({1, 0});

    sort(correctMoves.begin(), correctMoves.end());
    sort(rook.moves.begin(), rook.moves.end());

    assert(rook.moves == correctMoves);
}

void RookTest::emptyBoard(){
    Board board;
    Rook rook;
    rook.position = {1, 1};
    rook.color = Color::WHITE;
    rook.prepareMoves(board);
    vector<pair<int, int> > correctMoves;

    int i = 1;
    while(i+1<8){
        correctMoves.push_back({i + 1, 1});
        ++i;
    }
    i = 1;
    while(i-1>=0){
        correctMoves.push_back({i - 1, 1});
        --i;
    }

    int j = 1;
    while(j+1<8){
        correctMoves.push_back({1, j + 1});
        ++j;
    }
    j = 1;
    while(j-1>=0){
        correctMoves.push_back({1, j - 1});
        --j;
    }

    sort(correctMoves.begin(), correctMoves.end());
    sort(rook.moves.begin(), rook.moves.end());

    assert(rook.moves == correctMoves);
}

void RookTest::opponentPieceUp(){
    Board board;
    Rook rook;
    rook.position = {5, 5};
    rook.color = Color::WHITE;
    board.board[5][6] = Helper::createRook(Color::BLACK,  {5, 6});
    board.board[5][6]->color = Color::BLACK;

    rook.prepareMoves(board);

    vector<pair<int, int> > correctMoves;
    correctMoves.push_back({5, 6});

    int i = 5;
    while(i+1<8){
        correctMoves.push_back({i + 1, 5});
        ++i;
    }
    i = 5;
    while(i-1>=0){
        correctMoves.push_back({i - 1, 5});
        --i;
    }

    int j = 5;
    while(j-1>=0){
        correctMoves.push_back({5, j - 1});
        --j;
    }

    sort(correctMoves.begin(), correctMoves.end());
    sort(rook.moves.begin(), rook.moves.end());

    assert(rook.moves == correctMoves);
}