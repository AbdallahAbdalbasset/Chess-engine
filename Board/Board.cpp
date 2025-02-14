#include "Board.h"
#include "Pieces/Headers/Piece.h"
#include "Pieces/Headers/Pawn.h"
#include "Pieces/Headers/Rook.h"
#include "Pieces/Headers/Knight.h"
#include "Pieces/Headers/Bishop.h"
#include "Pieces/Headers/Queen.h"
#include "Pieces/Headers/King.h"
#include "../Helper/Helper.h"
#include "../Helper/enum.h"
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
Board::Board():board(vector<vector<shared_ptr<Piece>> >(8, vector<shared_ptr<Piece>>(8))){}

void Board::initializeBoard(){
    for(int i=0; i<8; i++){
        board[i][1] = Helper::createPawn(WHITE, {i, 1});
    }

    for(int i=0; i<8; i++){
        board[i][6] = Helper::createPawn(BLACK, {i, 6});
    }

    board[0][0] = Helper::createRook(WHITE, {0, 0});
    board[7][0] = Helper::createRook(WHITE, {0, 7});

    board[0][7] = Helper::createRook(BLACK, {7, 0});
    board[7][7] = Helper::createRook(BLACK, {7, 7});

    board[1][0] = Helper::createKnight(WHITE, {1, 0});
    board[6][0] = Helper::createKnight(WHITE, {6, 0});

    board[1][7] = Helper::createKnight(BLACK, {1, 7});
    board[6][7] = Helper::createKnight(BLACK, {6, 7});

    board[2][0] = Helper::createBishop(WHITE, {2, 0});
    board[5][0] = Helper::createBishop(WHITE, {5, 0});

    board[2][7] = Helper::createBishop(BLACK, {2, 7});
    board[5][7] = Helper::createBishop(BLACK, {5, 7});

    board[3][0] = Helper::createQueen(WHITE, {3, 0});

    board[3][7] = Helper::createQueen(BLACK, {3, 7});

    board[4][0] = Helper::createKing(WHITE, {4, 0});

    board[4][7] = Helper::createKing(BLACK, {4, 7});
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