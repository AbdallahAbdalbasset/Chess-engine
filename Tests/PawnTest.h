#pragma once
#include "../Board/Pieces/Headers/Pawn.h"
#include "../Board/Board.h"
#include "../Helper/enum.h"
#include <iostream>

class PawnTest{
    public:
    void runAllTests(){
        emptyBoardWhite();
        emptyBoardBlack();
        allMovesAreValid();
        
        cout<<"Pawn tests done"<<endl;
    }
    void emptyBoardWhite();
    void emptyBoardBlack();
    void allMovesAreValid();
};

void PawnTest::emptyBoardWhite(){
    Board board;
    Pawn pawn;
    pawn.position = {1,2};
    pawn.color = Color::WHITE;
    pawn.prepareMoves(board);
    vector<pair<int, int> > correctMoves;
    correctMoves.push_back({1, 3});
    assert(pawn.moves == correctMoves);
}

void PawnTest::emptyBoardBlack(){
    Board board;
    Pawn pawn;
    pawn.position = {1, 7};
    pawn.color = Color::BLACK;
    pawn.prepareMoves(board);
    vector<pair<int, int> > correctMoves;
    correctMoves.push_back({1,6});
    assert(pawn.moves == correctMoves);
}

void PawnTest::allMovesAreValid(){
    Board board;
    Pawn pawn;
    pawn.position = {4, 2};
    pawn.color = Color::WHITE;
        
    Pawn opponent1;
    Pawn opponent2;
    opponent1.color = Color::BLACK;
    opponent2.color = Color::BLACK;

    board.board[3][3] = &opponent1;
    board.board[5][3] = &opponent2;

    pawn.prepareMoves(board);

    vector<pair<int, int> > correctMoves;
    correctMoves.push_back({4, 3});
    correctMoves.push_back({3, 3});
    correctMoves.push_back({5, 3});

    sort(correctMoves.begin(), correctMoves.end());
    sort(pawn.moves.begin(), pawn.moves.end());
        
    assert(pawn.moves == correctMoves);
}