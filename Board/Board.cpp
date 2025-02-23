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
    board[7][0] = Helper::createRook(WHITE, {7, 0});

    board[0][7] = Helper::createRook(BLACK, {0, 7});
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
    for(char i = 'a'; i <= 'h'; i++)cout<<setw(6)<<left<<i;cout<<endl;
    cout<<endl;

    for(int i = boardSize - 1;i >= 0; i--){
        cout<<setw(6)<<i+1<<left;
        for(int j = 0;j < boardSize; j++){
            if(board[j][i]!=nullptr){
                string out = ((board[j][i]->color == Color::WHITE) ?  "W" : "B") + board[j][i]->name;
                cout << setw(6) << left <<  out;
            }else
                cout << setw(6) << left << "--";
        }
        cout<<setw(6)<<left<<i+1<<endl<<endl;
    }

    cout<<setw(6)<<left<<"";
    for(char i = 'a'; i <= 'h'; i++)cout<<setw(6)<<left<<i;cout<<endl;

}

void Board::prepareMoves(){

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(board[i][j]==nullptr) continue;

            board[i][j]->prepareMoves(*this);
        }
    }

}

bool Board::canKingSideCasle(Color color){
    if(color == Color::WHITE){
        if(!whiteKingSideCasle) return false;
        
        if(board[4][0]==nullptr||board[7][0]==nullptr)return false;
        if(board[4][0]->name != "K" || board[7][0]->name != "R") return false;
        
        if(Helper::isCheck(*this, Color::WHITE)) return false;
        
        int i = 5;
        while(i<7) if(board[i++][0]!=nullptr)return false;
        
        i = 5;
        while(i<7){
            board[i][0] = board[4][0];
            board[4][0] = nullptr;

            bool check = Helper::isCheck(*this, Color::WHITE);

            board[4][0] = board[i][0];
            board[i][0] = nullptr;

            i++;
            if(check)return false;
        } 
    }else{
        if(!blackKingSideCasle) return false;
        
        if(board[4][7]==nullptr||board[7][7]==nullptr)return false;
        if(board[4][7]->name != "K" || board[7][7]->name != "R") return false;
        
        if(Helper::isCheck(*this, Color::BLACK)) return false;
        
        int i = 5;
        while(i<7) if(board[i++][7]!=nullptr)return false;
        
        i = 5;
        while(i<7){
            board[i][7] = board[4][7];
            board[4][7] = nullptr;

            bool check = Helper::isCheck(*this, Color::BLACK);

            board[4][7] = board[i][7];
            board[i][7] = nullptr;

            i++;
            if(check) return false;
        }
    }

    return true;
}

bool Board::canQueenSideCasle(Color color){
    if(color == Color::WHITE){
        if(!whiteQueenSideCasle) return false;
        
        if(board[4][0]==nullptr||board[0][0]==nullptr)return false;
        if(board[4][0]->name != "K" || board[0][0]->name != "R") return false;
        
        if(Helper::isCheck(*this, Color::WHITE)) return false;
        
        int i = 1;
        while(i<4) if(board[i++][0]!=nullptr)return false;
        
        i = 1;
        while(i<4){
            board[i][0] = board[4][0];
            board[4][0] = nullptr;

            bool check = Helper::isCheck(*this, Color::WHITE);

            board[4][0] = board[i][0];
            board[i][0] = nullptr;

            i++;
            if(check) return false;
        }        
    }else{
        if(!blackQueenSideCasle) return false;
        
        if(board[4][7]==nullptr||board[0][7]==nullptr)return false;
        if(board[4][7]->name != "K" || board[0][7]->name != "R") return false;
        
        if(Helper::isCheck(*this, Color::BLACK)) return false;
        
        int i = 1;
        while(i<4) if(board[i++][7]!=nullptr)return false;
        
        i = 1;
        while(i<4){
            board[i][7] = board[4][7];
            board[4][7] = nullptr;

            bool check = Helper::isCheck(*this, Color::BLACK);

            board[4][7] = board[i][7];
            board[i][7] = nullptr;

            i++;
            if(check) return false;
        }
    }

    return true;
}

void Board::calcMovesThatToucheThePosition(Board& board, pair<int, int> from){

    string unAffected = "BN";
    for(int i = from.first+1;i<8;i++){
        if(board.board[from.first][i] == nullptr || unAffected.find(board.board[from.first][i]->name) == string::npos)continue;
        board.board[from.first][i]->prepareMoves(*this);
        break;
    }
    for(int i = from.first-1;i>=0;i--){
        if(board.board[from.first][i] == nullptr || unAffected.find(board.board[from.first][i]->name) == string::npos)continue;
        board.board[from.first][i]->prepareMoves(*this);
        break;
    }

    for(int i = from.second+1;i<8;i++){
        if(board.board[i][from.second] == nullptr || unAffected.find(board.board[i][from.second]->name) == string::npos)continue;
        board.board[i][from.second]->prepareMoves(*this);
        break;
    }
    for(int i = from.second-1;i>=0;i--){
        if(board.board[i][from.second] == nullptr || unAffected.find(board.board[i][from.second]->name) == string::npos)continue;
        board.board[i][from.second]->prepareMoves(*this);
        break;
    }

    unAffected = "NR";
    int i = from.first+1;
    int j = from.second+1;
    while(Helper::isInBoard(i,  j)){
        if(board.board[i][j] != nullptr && unAffected.find(board.board[i][j]->name) == string::npos) {board.board[i][j]->prepareMoves(*this);break;}
        i++;j++;
    }

    i = from.first-1;
    j = from.second-1;
    while(Helper::isInBoard(i, j)){
        if(board.board[i][j] != nullptr && unAffected.find(board.board[i][j]->name) == string::npos) {board.board[i][j]->prepareMoves(*this);break;}
        i--;j--;
    }

    i = from.first+1;
    j = from.second-1;
    while(Helper::isInBoard(i, j)){
        if(board.board[i][j] != nullptr && unAffected.find(board.board[i][j]->name) == string::npos) {board.board[i][j]->prepareMoves(*this);break;}
        i++;j--;
    }

    i = from.first-1;
    j = from.second+1;
    while(Helper::isInBoard(i, j)){
        if(board.board[i][j] != nullptr && unAffected.find(board.board[i][j]->name) == string::npos) {board.board[i][j]->prepareMoves(*this);break;}
        i--;j++;
    }

}
void Board::reprepareMoves(pair<int, int> from, pair<int, int> to){
    if(board[from.first][from.second] != nullptr) board[from.first][from.second]->prepareMoves(*this);
    if(board[to.first][to.second] != nullptr) board[to.first][to.second]->prepareMoves(*this);
    calcMovesThatToucheThePosition(*this, from);
    calcMovesThatToucheThePosition(*this, to);
}