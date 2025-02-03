#pragma once
#include "../Board/Pieces/Headers/Queen.h"
#include "../Board/Board.h"
#include "../Helper/enum.h"

class QueenTest {
    public:
    void runAllTests(){
        fourMoves();
        emptyBoard();
        opponentPieceUp();
        opponentPieceUpRight();

        cout<<"Queen tests done"<<endl;
    }

    void fourMoves();
    void emptyBoard();
    void opponentPieceUp();
    void opponentPieceUpRight();

};

void QueenTest::fourMoves(){
    Board board;
    Queen queen;
    queen.position = {0, 0};
    queen.color = Color::WHITE;

    board.board[1][0] = new Queen();
    board.board[1][0]->color = Color::WHITE;
    board.board[0][1] = new Queen();
    board.board[0][1]->color = Color::WHITE;
    board.board[1][1] = new Queen();
    board.board[1][1]->color = Color::WHITE;
    queen.prepareMoves(board);

    vector<pair<int, int> > correctMoves;
    correctMoves.push_back({1, 0});
    correctMoves.push_back({0, 1});
    correctMoves.push_back({1, 1});

    sort(correctMoves.begin(), correctMoves.end());
    sort(queen.moves.begin(), queen.moves.end());

    assert(queen.moves == correctMoves);
}

void QueenTest::emptyBoard(){
    Board board;
    Queen queen;
    queen.position = {3, 3};
    queen.color = Color::WHITE;
    queen.prepareMoves(board);

    vector<pair<int, int> > correctMoves;
    int i = 3;
    int j = 3;
    while(i + 1 < 8 && j + 1 < 8){
        correctMoves.push_back({++i, ++j});
    }

    i = 3;
    j = 3;
    while(i - 1 >= 0 && j - 1 >= 0){
        correctMoves.push_back({--i, --j});
    }

    i = 3;
    j = 3;
    while(i + 1 < 8 && j - 1 >= 0){
        correctMoves.push_back({++i, --j});
    }

    i = 3;
    j = 3;
    while(i - 1 >= 0 && j + 1 < 8){
        correctMoves.push_back({--i, ++j});
    }

    i = 3;
    j = 3;
    while(i + 1 < 8){
        correctMoves.push_back({++i, 3});
    }

    i = 3;
    while(i - 1 >= 0){
        correctMoves.push_back({--i, 3});
    }

    i = 3;
    while(j + 1 < 8){
        correctMoves.push_back({3, ++j});
    }

    j = 3;
    while(j - 1 >= 0){
        correctMoves.push_back({3, --j});
    }

    sort(correctMoves.begin(), correctMoves.end());
    sort(queen.moves.begin(), queen.moves.end());

    assert(queen.moves == correctMoves);
}

void QueenTest::opponentPieceUp(){
    Board board;
    Queen queen;
    queen.position = {3, 3};
    queen.color = Color::WHITE;

    board.board[3][4] = new Queen();
    board.board[3][4]->color = Color::BLACK;

    queen.prepareMoves(board);
    
    vector<pair<int, int> > correctMoves;
    correctMoves.push_back({3, 4});

    int i = 3;
    int j = 3;
    while(i + 1 < 8 && j + 1 < 8){
        correctMoves.push_back({++i, ++j});
    }

    i = 3;
    j = 3;
    while(i - 1 >= 0 && j - 1 >= 0){
        correctMoves.push_back({--i, --j});
    }

    i = 3;
    j = 3;
    while(i + 1 < 8 && j - 1 >= 0){
        correctMoves.push_back({++i, --j});
    }

    i = 3;
    j = 3;
    while(i - 1 >= 0 && j + 1 < 8){
        correctMoves.push_back({--i, ++j});
    }

    i = 3;
    j = 3;
    while(i + 1 < 8){
        correctMoves.push_back({++i, 3});
    }

    i = 3;
    while(i - 1 >= 0){
        correctMoves.push_back({--i, 3});
    }

    j = 3;
    while(j - 1 >= 0){
        correctMoves.push_back({3, --j});
    }

    sort(correctMoves.begin(), correctMoves.end());
    sort(queen.moves.begin(), queen.moves.end());

    assert(queen.moves == correctMoves);
}

void QueenTest::opponentPieceUpRight(){
    Board board;
    Queen queen;
    queen.position = {3, 3};
    queen.color = Color::WHITE;

    board.board[4][4] = new Queen();
    board.board[4][4]->color = Color::BLACK;

    queen.prepareMoves(board);

    vector<pair<int, int> > correctMoves;
    correctMoves.push_back({4, 4});

    int i = 3;
    int j = 3;
    while(i - 1 >= 0 && j - 1 >= 0){
        correctMoves.push_back({--i, --j});
    }

    i = 3;
    j = 3;
    while(i - 1 >= 0 && j + 1 < 8){
        correctMoves.push_back({--i, ++j});
    }

    i = 3;
    j = 3;
    while(i + 1 < 8 && j - 1 >= 0){
        correctMoves.push_back({++i, --j});
    }

    i = 3;
    j = 3;
    while(i + 1 < 8){
        correctMoves.push_back({++i, 3});
    }

    i = 3;
    while(i - 1 >= 0){
        correctMoves.push_back({--i, 3});
    }

    j = 3;
    while(j - 1 >= 0){
        correctMoves.push_back({3, --j});
    }

    j = 3;
    while(j + 1 < 8){
        correctMoves.push_back({3, ++j});
    }

    sort(correctMoves.begin(), correctMoves.end());
    sort(queen.moves.begin(), queen.moves.end());

    assert(queen.moves == correctMoves);
}