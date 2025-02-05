#include "Board/Board.h"
#include "Engine/Engine.h"
#include "Helper/Helper.h"
#include "Board/Pieces/Headers/King.h"
#include "Board/Pieces/Headers/Rook.h"
#include "Board/Pieces/Headers/Queen.h"
#include "Board/Pieces/Headers/Knight.h"
#include "Board/Pieces/Headers/Pawn.h"
#include "Helper/enum.h"
#include <iostream>

using namespace std;

class Game{
    public:
    void startGame();
    void napilion(Board&);
    void knightsAndTwoRooks(Board&);
    void initialBoard(Board&);
    void promotion(Board&);
    void mateWithRook(Board&);
};

void Game::initialBoard(Board& board){
    board.initializeBoard();
}

void Game::knightsAndTwoRooks(Board& board){
    board.board[0][0] = Helper::createKing(Color::BLACK, {0, 0});
    board.board[1][6] = Helper::createKnight(Color::BLACK, {1, 6});
    board.board[2][6] = Helper::createKnight(Color::BLACK, {2, 6});

    board.board[3][3] = Helper::createKing(Color::WHITE, {3, 3});
    board.board[6][2] = Helper::createRook(Color::WHITE, {6, 2});
    board.board[5][3] = Helper::createRook(Color::WHITE, {5, 3});

    board.board[6][4] = Helper::createPawn(Color::WHITE, {6, 4});
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

void Game::promotion(Board& board){
    board.board[0][6] = Helper::createPawn(Color::WHITE, {0, 6});
    board.board[1][6] = Helper::createRook(Color::WHITE, {1, 6});

    board.board[0][7] = Helper::createPawn(Color::BLACK, {0, 7});
    board.board[1][7] = Helper::createRook(Color::BLACK, {1, 7});
    board.board[7][7] = Helper::createKing(Color::BLACK, {7, 7});
}

void Game::mateWithRook(Board& board){
    board.board[0][1] = Helper::createRook(Color::WHITE, {0, 1});
    board.board[1][1] = Helper::createKing(Color::WHITE, {1, 1});

    board.board[7][7] = Helper::createKing(Color::BLACK, {7, 7});
}

void Game::startGame(){
    Board board;
    knightsAndTwoRooks(board);

    board.prepareMoves();
    board.printBoard();

    while(1){
        int c;
        cout<<"0 Print valid moves for specific Piece"<<endl;
        cout<<"1 The engine will play white move"<<endl;
        cout<<"2 The engine will play black move"<<endl;
        cout<<"3 Play a move manually"<<endl;
        while(cin>>c){
            pair<int, int> from, to;
            pair<pair<int, int>, pair<pair<int, int>, int>> ret;

            if(c == 0){// Print valid moves for specific Piece
                cout<<"Enter the position of the piece: ";
                cin>>from.first>>from.second;
                for(auto&i:board.board[from.first][from.second]->moves)
                    cout<<i.first<<i.second<<" ";cout<<endl;
                continue;
            }else if(c == 1){// white move
                cout<<"Calculating..."<<endl;
                ret = Engine::getMove(board, Color::WHITE, 0, INT_MIN, INT_MAX);

                Helper::playMove(board, ret.first, ret.second.first, board.board[ret.first.first][ret.first.second], nullptr);
            }else if(c == 2){// black move
                cout<<"Calculating..."<<endl;
                ret = Engine::getMove(board, Color::BLACK, 0, INT_MIN, INT_MAX);

                Helper::playMove(board, ret.first, ret.second.first, board.board[ret.first.first][ret.first.second], nullptr);
            }else{// Play a move manually
                cout<<"Enter the from and to positions: ";
                cin>>from.first>>from.second>>to.first>>to.second;
                Helper::playMove(board, from, to, board.board[from.first][from.second], nullptr);
                ret.second.second = 1;
            }
            board.prepareMoves();
            board.printBoard();

            if(ret.second.second == whiteCheckMate) { cout << "White Win :)" << endl; return; }
            if(ret.second.second == blackCheckMate) { cout << "Black Win :)" << endl; return; }

            cout<<"0 Print valid moves for specific Piece"<<endl;
            cout<<"1 The engine will play white move"<<endl;
            cout<<"2 The engine will play black move"<<endl;
            cout<<"3 Play a move manually"<<endl;
        }
    }
}