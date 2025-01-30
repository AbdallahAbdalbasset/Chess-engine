#pragma once
#include "../Board/Pieces/Headers/Bishop.h"
#include "../Board/Board.h"
#include "../Helper/enum.h"
#include <iostream>

class BishopTest {
    public:
    void runAllTests(){
        noMoves();
        emptyBoard();
        opponentPieceUpRight();

        cout<<"Bishop tests done"<<endl;
    }

    void noMoves();
    void emptyBoard();
    void opponentPieceUpRight();

};

void BishopTest::noMoves(){
    Board board;
    Bishop bishop;
    bishop.position = {2, 0};
    bishop.color = Color::WHITE;

    board.board[1][1] = new Bishop();
    board.board[1][1]->color = Color::WHITE;
    board.board[3][1] = new Bishop();
    board.board[3][1]->color = Color::WHITE;

    bishop.prepareMoves(board);

    assert(bishop.moves.empty());
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

    board.board[6][6] = new Bishop();
    board.board[6][6]->color = Color::BLACK;

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