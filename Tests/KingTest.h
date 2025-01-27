#pragma once
#include "../Board/Pieces/King.h"
#include "../Board/Board.h"
#include "../Helper/enum.h"
#include <iostream>

class KingTest {
    public:
    void runAllTests(){
        noMoves();
        emptyBoard();
        opponentPieceUpRight();

        cout<<"King tests done"<<endl;
    }

    void noMoves();
    void emptyBoard();
    void opponentPieceUpRight();
};

void KingTest::noMoves(){
    Board board;
    King king;
    king.position = {0, 0};
    king.color = Color::WHITE;
    
    board.board[1][1] = new King();
    board.board[1][1]->color = Color::WHITE;
    board.board[0][1] = new King();
    board.board[0][1]->color = Color::WHITE;
    board.board[1][0] = new King();
    board.board[1][0]->color = Color::WHITE;

    king.prepareMoves(board);

    assert(king.moves.empty());
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
    
    board.board[4][4] = new King();
    board.board[4][4]->color = Color::BLACK;

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