#pragma once
#include "Board.h"
#include "Pieces/Headers/Piece.h"
#include "Pieces/Headers/Pawn.h"
#include "Pieces/Headers/Rook.h"
#include "Pieces/Headers/Knight.h"
#include "Pieces/Headers/Bishop.h"
#include "Pieces/Headers/Queen.h"
#include "Pieces/Headers/King.h"
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
Board::Board():board(vector<vector<Piece*> >(8, vector<Piece*>(8, nullptr))){}

Piece* createPawn(Color color, pair<int, int> position){
    Piece* pawn = new Pawn;
    pawn->position = position;
    pawn->name = "P";
    pawn->value = 1;
    pawn->color = color;
    return pawn;
}  

Piece* createRook(Color color, pair<int, int> position){
    Piece* rook = new Rook;
    rook->position = position;
    rook->name = "R";
    rook->value = 5;
    rook->color = color;
    return rook;
}

Piece* createKnight(Color color, pair<int, int> position){
    Piece* knight = new Knight;
    knight->position = position;
    knight->name = "N";
    knight->value = 3;
    knight->color = color;
    return knight;
}

Piece* createBishop(Color color, pair<int, int> position){
    Piece* bishop = new Bishop;
    bishop->position = position;
    bishop->name = "B";
    bishop->value = 3;
    bishop->color = color;
    return bishop;
}

Piece* createQueen(Color color, pair<int, int> position){
    Piece* queen = new Queen;
    queen->position = position;
    queen->name = "Q";
    queen->value = 9;
    queen->color = color;
    return queen;
}

Piece* createKing(Color color, pair<int, int> position){
    Piece* king = new King();
    king->position = position;
    king->name = "K";
    king->value = 0;
    king->color = color;
    return king;
}


void Board::initializeBoard(){
    for(int i=0; i<8; i++){
        board[i][1] = createPawn(WHITE, {i, 1});
    }

    for(int i=0; i<8; i++){
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
    system("clear");
    cout<<endl<<endl;

    cout<<setw(6)<<left<<"";
    for(int i = 0; i < boardSize; i++)cout<<setw(6)<<left<<i;cout<<endl;
    cout<<endl;

    for(int i = boardSize - 1;i >= 0; i--){
        cout<<setw(6)<<i<<left;
        for(int j = 0;j < boardSize; j++){
            if(board[j][i]!=nullptr){
                string out = ((board[j][i]->color == Color::WHITE) ?  "W" : "B") + board[j][i]->name;
                cout << setw(6) << left <<  out;
            }else
                cout << setw(6) << left << "--";
        }
        cout<<setw(6)<<left<<i<<endl<<endl;
    }

    cout<<setw(6)<<left<<"";
    for(int i = 0; i < boardSize; i++)cout<<setw(6)<<left<<i;cout<<endl;

}

void Board::prepareMoves(){
    vector<set<pair<int, int> > > allMoves(2);
    vector<pair<int, int> > kingsPositions;

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(board[i][j]==nullptr) continue;

            board[i][j]->prepareMoves(*this);
            if(board[i][j]->name == "K"){
                kingsPositions.push_back({i, j});
            }
            for(auto& move : board[i][j]->moves){
                allMoves[board[i][j]->color == Color::WHITE ? 0 : 1].insert(move);
            }
        }
    }

    for(auto& kingPostion :  kingsPositions){
        vector<pair<int, int> > kingMoves;

        for(auto&  kingMove : board[kingPostion.first][kingPostion.second]->moves){
            if(allMoves[board[kingPostion.first][kingPostion.second]->color == Color::WHITE? 1 : 0].find(kingMove)== allMoves[board[kingPostion.first][kingPostion.second]->color == Color::WHITE? 1 : 0].end()){
                kingMoves.push_back(kingMove);
            }
        }

        board[kingPostion.first][kingPostion.second]->moves = kingMoves;
    }
}