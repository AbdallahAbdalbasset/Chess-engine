#include "Board/Board.h"
#include "Engine/Engine.h"
#include "Helper/Helper.h"
#include "Board/Pieces/Headers/King.h"
#include "Board/Pieces/Headers/Rook.h"
#include "Board/Pieces/Headers/Queen.h"
#include "Board/Pieces/Headers/Knight.h"
#include "Board/Pieces/Headers/Pawn.h"
#include <iostream>

using namespace std;

class Game{
    public:
    void napilion(Board&);
    void startGame();
    void twoRooksVsKing(Board&);
    void rookAndAQueen(Board&);
    void knightAndTwoRooks(Board&);
    void initialBoard(Board&);
};

void Game::initialBoard(Board& board){
    board.initializeBoard();
}

void Game::knightAndTwoRooks(Board& board){
    board.board[0][0] = new King;
    board.board[0][0]->color = Color::WHITE;
    board.board[0][0]->position = {0, 0};
    board.board[0][0]->name = "K";

    board.board[1][6] = new Knight;
    board.board[1][6]->color = Color::BLACK;
    board.board[1][6]->position = {1, 6};
    board.board[1][6]->name = "N";
    board.board[1][6]->value = 3;

    board.board[2][6] = new Knight;
    board.board[2][6]->color = Color::BLACK;
    board.board[2][6]->position = {2, 6};
    board.board[2][6]->name = "N";
    board.board[2][6]->value = 3;

    board.board[6][2] = new Rook;
    board.board[6][2]->color = Color::WHITE;
    board.board[6][2]->position = {6, 2};
    board.board[6][2]->name = "R";
    board.board[6][2]->value = 5;

    board.board[6][3] = new Rook;
    board.board[6][3]->color = Color::WHITE;
    board.board[6][3]->position = {6, 3};
    board.board[6][3]->name = "R";
    board.board[6][3]->value = 5;

    board.board[6][4] = new Pawn;
    board.board[6][4]->color = Color::WHITE;
    board.board[6][4]->position = {6, 4};
    board.board[6][4]->name = "P";
    board.board[6][4]->value = 1;
}

void Game::rookAndAQueen(Board& board){
board.board[5][1] = new King;
    board.board[5][1]->color = Color::WHITE;
    board.board[5][1]->position = {5, 1};
    board.board[5][1]->name = "K";

    board.board[0][7] = new Queen;
    board.board[0][7]->color = Color::BLACK;
    board.board[0][7]->position = {0, 7};
    board.board[0][7]->name = "Q";
    board.board[0][7]->value = 9;

    board.board[1][6] = new Rook;
    board.board[1][6]->color = Color::BLACK;
    board.board[1][6]->position = {1, 6};
    board.board[1][6]->name = "R";
    board.board[1][6]->value = 5;
}

void Game::twoRooksVsKing(Board& board){
    board.board[5][1] = new King;
    board.board[5][1]->color = Color::WHITE;
    board.board[5][1]->position = {5, 1};
    board.board[5][1]->name = "K";

    board.board[0][7] = new Rook;
    board.board[0][7]->color = Color::BLACK;
    board.board[0][7]->position = {0, 7};
    board.board[0][7]->name = "R";
    board.board[0][7]->value = 5;

    board.board[1][6] = new Rook;
    board.board[1][6]->color = Color::BLACK;
    board.board[1][6]->position = {1, 6};
    board.board[1][6]->name = "R";
    board.board[1][6]->value = 5;
}

void Game::napilion(Board& board){
    board.initializeBoard();
    
    board.board[5][2] = board.board[3][0];
    board.board[3][0] = nullptr;
    board.board[5][2]->position = {5, 2};

    board.board[2][3] = board.board[5][0];
    board.board[5][0] = nullptr;
    board.board[2][3]->position = {2, 3};

    board.board[4][6] = nullptr;
}

void Game::startGame(){
    Board board;
    initialBoard(board);

    board.prepareMoves();
    board.printBoard();

    while(1){
        int c;
        while(cin>>c){
            pair<int, int> from, to;
            if(c == 0){
                cin>>from.first>>from.second;
                for(auto&i:board.board[from.first][from.second]->moves)
                    cout<<i.first<<i.second<<" ";cout<<endl;
                    continue;
            }else if(c == 1){
                cout<<"Calculating..."<<endl;
                auto ret = Engine::getMove(board, Color::WHITE, 0);
                if(ret.first.first == -1){cout<<"It is chemate stupid!"<<endl; continue;}
                
                cout<<ret.first.first<<ret.first.second<<" "<<ret.second.first.first<<ret.second.first.second<<endl;
                Helper::playMove(board, ret.first, ret.second.first);
            }else if(c == 2){
                cout<<"Calculating..."<<endl;
                auto ret = Engine::getMove(board, Color::BLACK, 0);
                if(ret.first.first == -1){cout<<"It is chemate stupid!"<<endl;continue;}
                cout<<ret.first.first<<ret.first.second<<" "<<ret.second.first.first<<ret.second.first.second<<endl;
                Helper::playMove(board, ret.first, ret.second.first);
            }else{
                cin>>from.first>>from.second>>to.first>>to.second;
                Helper::playMove(board, from, to);
            }
            board.prepareMoves();
            board.printBoard();
        }
    }
}