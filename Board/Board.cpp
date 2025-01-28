#pragma once
#include "Board.h"
#include "Pieces/Headers/Pawn.h"
#include "Pieces/Headers/Rook.h"
#include "Pieces/Headers/Knight.h"
#include "Pieces/Headers/Bishop.h"
#include "Pieces/Headers/Queen.h"
#include "Pieces/Headers/King.h"
#include <iomanip>
#include <iostream>

using namespace std;
Board::Board():board(vector<vector<Piece*> >(8, vector<Piece*>(8, nullptr))){}

Pawn* createPawn(Color color, pair<int, int> position){
    Pawn* pawn = new Pawn();
    pawn->position = position;
    pawn->name = "P";
    pawn->value = 1;
    pawn->color = color;
    return pawn;
}  

Rook* createRook(Color color, pair<int, int> position){
    Rook* rook = new Rook();
    rook->position = position;
    rook->name = "R";
    rook->value = 5;
    rook->color = color;
    return rook;
}

Knight* createKnight(Color color, pair<int, int> position){
    Knight* knight = new Knight();
    knight->position = position;
    knight->name = "N";
    knight->value = 3;
    knight->color = color;
    return knight;
}

Bishop* createBishop(Color color, pair<int, int> position){
    Bishop* bishop = new Bishop();
    bishop->position = position;
    bishop->name = "B";
    bishop->value = 3;
    bishop->color = color;
    return bishop;
}

Queen* createQueen(Color color, pair<int, int> position){
    Queen* queen = new Queen();
    queen->position = position;
    queen->name = "Q";
    queen->value = 9;
    queen->color = color;
    return queen;
}

King* createKing(Color color, pair<int, int> position){
    King* king = new King();
    king->position = position;
    king->name = "K";
    king->value = 0;
    king->color = color;
    return king;
}


void Board::initializeBoard(){
    for(int i=0; i<boardSize; i++){
        board[i][1] = createPawn(WHITE, {i, 1});
    }

    for(int i=0; i<boardSize; i++){
        board[i][6] = createPawn(BLACK, {i, 6});
    }

    board[0][0] = createRook(WHITE, {0, 0});
    board[7][0] = createRook(WHITE, {0, 7});

    board[0][7] = createRook(BLACK, {7, 0});
    board[7][7] = createRook(BLACK, {7, 7});

    board[1][0] = createKnight(WHITE, {1, 0});
    board[6][0] = createKnight(WHITE, {6, 0});

    board[1][7] = createKnight(BLACK, {1, 7});
    board[6][7] = createKnight(BLACK, {6, 7});

    board[2][0] = createBishop(WHITE, {2, 0});
    board[5][0] = createBishop(WHITE, {5, 0});

    board[2][7] = createBishop(BLACK, {2, 7});
    board[5][7] = createBishop(BLACK, {5, 7});

    board[3][0] = createQueen(WHITE, {3, 0});

    board[3][7] = createQueen(BLACK, {3, 7});

    board[4][0] = createKing(WHITE, {4, 0});

    board[4][7] = createKing(BLACK, {4, 7});
}
void Board::printBoard(){
    cout<<endl<<endl;
    for(int i = boardSize - 1;i >= 0; i--){
        for(int j = 0;j < boardSize; j++){
            if(board[j][i]!=nullptr){
                string out = ((board[j][i]->color == Color::WHITE) ?  "W" : "B") + board[j][i]->name;
                cout << setw(6) << left <<  out;
            }else
                cout << setw(6) << left << "--";
        }
        cout<<endl<<endl;
    }
}