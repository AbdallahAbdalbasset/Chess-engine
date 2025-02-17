#include "Board/Board.h"
#include "Engine/Engine.h"
#include "Helper/Helper.h"
#include "Board/Pieces/Headers/King.h"
#include "Board/Pieces/Headers/Rook.h"
#include "Board/Pieces/Headers/Queen.h"
#include "Board/Pieces/Headers/Knight.h"
#include "Board/Pieces/Headers/Pawn.h"
#include "Helper/enum.h"
#include <chrono>
#include <iostream>
#include <map>

using namespace std;

class Game{
    public:
    void startGame();
    void napilion(Board&);
    void knightsAndTwoRooks(Board&);
    void initialBoard(Board&);
    void promotion(Board&);
    void mateWithRook(Board&);
    void checkmateWithPromotion(Board&);
    void twoPawnsOn6(Board&);
    void lichessBuzzleMateInThree(Board&);
    void lichessBuzzleMateInThreeWithKnight(Board&);
    void testFullGame();
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



void Game::checkmateWithPromotion(Board& board){
    board.board[6][1] = Helper::createRook(Color::WHITE, {6, 1});
    board.board[7][6] = Helper::createPawn(Color::WHITE, {7, 6});
    board.board[0][7] = Helper::createKing(Color::WHITE, {0, 7});

    board.board[0][0] = Helper::createKing(Color::BLACK, {0, 0});
}


void Game::twoPawnsOn6(Board& board){
    board.board[0][0] = Helper::createKing(Color::WHITE, {0, 0});

    board.board[7][0] = Helper::createKing(Color::BLACK, {7, 0});
    board.board[7][6] = Helper::createPawn(Color::WHITE, {7, 6});
    board.board[6][6] = Helper::createPawn(Color::WHITE, {6, 6});
}

void Game::lichessBuzzleMateInThree(Board& board){
    board.board[7][1] = Helper::createPawn(Color::WHITE, {7, 1});
    board.board[6][1] = Helper::createPawn(Color::WHITE, {6, 1});
    board.board[5][1] = Helper::createPawn(Color::WHITE, {5, 1});

    board.board[6][0] = Helper::createKing(Color::WHITE, {6, 0});

    board.board[3][2] = Helper::createBishop(Color::WHITE, {3, 2});
    board.board[6][4] = Helper::createBishop(Color::WHITE, {6, 4});

    board.board[7][2] = Helper::createRook(Color::WHITE, {7, 2});
    
    board.board[3][4] = Helper::createKnight(Color::WHITE, {3, 4});


    board.board[7][5] = Helper::createPawn(Color::BLACK, {7, 5});
    board.board[6][6] = Helper::createPawn(Color::BLACK, {6, 6});
    board.board[5][6] = Helper::createPawn(Color::BLACK, {5, 6});
    board.board[4][5] = Helper::createPawn(Color::BLACK, {4, 5});

    board.board[6][7] = Helper::createKing(Color::BLACK, {6, 7});

    board.board[5][7] = Helper::createRook(Color::BLACK, {5, 7});

    board.board[2][7] = Helper::createBishop(Color::BLACK, {2, 7});
    board.board[4][6] = Helper::createBishop(Color::BLACK, {4, 6});

    board.board[0][4] = Helper::createQueen(Color::BLACK, {0, 4});
    board.board[1][3] = Helper::createRook(Color::BLACK, {1, 3});

    board.board[4][4] = Helper::createKnight(Color::BLACK, {4, 4});
}

void Game::lichessBuzzleMateInThreeWithKnight(Board& board){
    board.board[7][2] = Helper::createPawn(Color::WHITE, {7, 2});
    board.board[7][0] = Helper::createKing(Color::WHITE, {7, 0});
    board.board[6][1] = Helper::createBishop(Color::WHITE, {6, 1});
    board.board[6][0] = Helper::createRook(Color::WHITE, {7, 0});

    board.board[4][4] = Helper::createBishop(Color::BLACK, {4, 4});
    board.board[4][1] = Helper::createKnight(Color::BLACK, {4, 1});
    board.board[6][7] = Helper::createKing(Color::BLACK, {6, 7});
}

void Game::startGame(){
    Board board;
    initialBoard(board);

    board.prepareMoves();
    board.printBoard();

    while(1){
        int c;
        cout<<"0 Print valid moves for specific Piece"<<endl;
        cout<<"1 The engine will play white move"<<endl;
        cout<<"2 The engine will play black move"<<endl;
        cout<<"3 Play a move manually"<<endl;

        chrono::duration<double> duration;
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

                auto start = chrono::high_resolution_clock::now();

                ret = Engine::getMove(board, Color::WHITE);

                auto end = chrono::high_resolution_clock::now();
                duration = chrono::duration_cast<chrono::microseconds>(end - start);

                if(ret.first.first == -1) {cout<<"StaleMate "<<endl; return; }
                Helper::playMove(board, board.board[ret.first.first][ret.first.second]->color, ret.first, ret.second.first, board.board[ret.first.first][ret.first.second], nullptr);
            }else if(c == 2){// black move
                cout<<"Calculating..."<<endl;

                auto start = chrono::high_resolution_clock::now();

                ret = Engine::getMove(board, Color::BLACK);

                auto end = chrono::high_resolution_clock::now();
                duration = chrono::duration_cast<chrono::microseconds>(end - start);

                if(ret.first.first == -1) {cout<<"StaleMate "<<endl; return; }
                Helper::playMove(board, board.board[ret.first.first][ret.first.second]->color, ret.first, ret.second.first, board.board[ret.first.first][ret.first.second], nullptr);
            }else{// Play a move manually
                cout<<"Enter the from and to positions: ";

                cin>>from.first>>from.second>>to.first>>to.second;
                Helper::playMove(board, board.board[ret.first.first][ret.first.second]->color, from, to, board.board[from.first][from.second], nullptr);
                ret.second.second = 1;
            }
            board.prepareMoves();
            board.printBoard();

            cout<<"Time: " << duration.count() << " seconds"<<endl;

            if(ret.second.second == WHITECHECKMATE) { cout << "White Win :)" << endl; return; }
            if(ret.second.second == BLACKCHECKMATE) { cout << "Black Win :)" << endl; return; }
            if(Helper::isDraw(board)) { cout << "Draw!" << endl; return; }

            cout<<"0 Print valid moves for specific Piece"<<endl;
            cout<<"1 The engine will play white move"<<endl;
            cout<<"2 The engine will play black move"<<endl;
            cout<<"3 Play a move manually"<<endl;
        }
    }
}

void Game::testFullGame() {
    Board board;
    initialBoard(board);

    board.prepareMoves();
    bool turn = 1;
    int cnt = 1;
    map<int, char>mp;
    mp[0] = 'A';
    mp[1] = 'B';
    mp[2] = 'C';
    mp[3] = 'D';
    mp[4] = 'E';
    mp[5] = 'F';
    mp[6] = 'G';
    mp[7] = 'H';
    int x;
    while(cin>>x){
        auto move = Engine::getMove(board, turn?Color::WHITE:Color::BLACK);
        
        cout<<cnt<<" "<<(turn ? "WHITE" : "BLACK")<<" ";
        cout<<board.board[move.first.first][move.first.second]->name<<" "<<mp[move.first.first]<<move.first.second+1<<" "<<mp[move.second.first.first]<<move.second.first.second+1<<endl;
        if(move.first.first==-1||Helper::isDraw(board)){cout<<"End"<<endl;return;}

        Helper::playMove(board, turn?Color::WHITE:Color::BLACK, move.first, move.second.first, board.board[move.first.first][move.first.second], nullptr);
        board.printBoard();
        cnt++;
        turn = !turn;
        cout<<Engine::getScore(board)<<endl;
        cout<<board.canKingSideCasle(Color::WHITE)<<endl;
        cout<<board.canQueenSideCasle(Color::WHITE)<<endl;
        cout<<board.canKingSideCasle(Color::BLACK)<<endl;
        cout<<board.canQueenSideCasle(Color::BLACK)<<endl;
    }
}