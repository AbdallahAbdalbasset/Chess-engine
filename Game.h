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
    void ramyGame(Board&);
    void myGame(Board&);
    void myGameMateInThree(Board&);
    void mateIn6(Board&);
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

void Game::ramyGame(Board& board){
    
    board.whiteKingSideCasle = false;
    board.blackKingSideCasle = false;
    board.whiteQueenSideCasle = false;
    board.blackQueenSideCasle = false;

    board.board[7][7] = Helper::createRook(Color::WHITE, {7, 7});
    board.board[7][6] = Helper::createKing(Color::WHITE, {7, 6});
    board.board[1][0] = Helper::createKing(Color::WHITE, {1, 0});

}

void Game::myGame(Board& board){
    board.board[1][4] = Helper::createPawn(Color::BLACK, {1, 4});
    board.board[3][4] = Helper::createPawn(Color::BLACK, {3, 4});
    board.board[5][2] = Helper::createPawn(Color::BLACK, {5, 2});
    board.board[5][3] = Helper::createKing(Color::BLACK, {5, 3});

    board.board[7][2] = Helper::createKing(Color::WHITE, {7, 2});
    board.board[1][1] = Helper::createPawn(Color::WHITE, {1, 1});
    board.board[2][1] = Helper::createPawn(Color::WHITE, {2, 1});
    board.board[3][3] = Helper::createPawn(Color::WHITE, {3, 3});

    board.board[3][5] = Helper::createKnight(Color::WHITE, {3, 5});
}

void Game::myGameMateInThree(Board& board){
    board.board[0][1] = Helper::createPawn(Color::WHITE, {0, 1});
    board.board[1][2] = Helper::createPawn(Color::WHITE, {1, 2});
    board.board[2][1] = Helper::createPawn(Color::WHITE, {2, 1});
    board.board[5][1] = Helper::createPawn(Color::WHITE, {5, 1});
    board.board[6][1] = Helper::createPawn(Color::WHITE, {6, 1});
    board.board[7][1] = Helper::createPawn(Color::WHITE, {7, 1});

    board.board[2][3] = Helper::createBishop(Color::WHITE, {2, 3});

    board.board[0][0] = Helper::createRook(Color::WHITE, {0, 0});
    board.board[3][5] = Helper::createRook(Color::WHITE, {3, 5});

    board.board[5][6] = Helper::createKnight(Color::WHITE, {5, 6});

    board.board[6][0] = Helper::createKing(Color::WHITE, {6, 0});

    board.board[7][3] = Helper::createQueen(Color::WHITE, {7, 3});

    board.board[0][4] = Helper::createPawn(Color::BLACK, {0, 4});
    board.board[1][6] = Helper::createPawn(Color::BLACK, {1, 6});
    board.board[4][3] = Helper::createPawn(Color::BLACK, {4, 3});
    board.board[5][4] = Helper::createPawn(Color::BLACK, {5, 4});
    board.board[6][6] = Helper::createPawn(Color::BLACK, {6, 6});
    board.board[7][5] = Helper::createPawn(Color::BLACK, {7, 5});

    board.board[2][7] = Helper::createBishop(Color::BLACK, {2, 7});

    board.board[0][7] = Helper::createRook(Color::BLACK, {0, 7});
    board.board[5][7] = Helper::createRook(Color::BLACK, {5, 7});

    board.board[2][5] = Helper::createKnight(Color::BLACK, {2, 5});

    board.board[7][6] = Helper::createKing(Color::BLACK, {7, 6});

    board.board[1][5] = Helper::createQueen(Color::BLACK, {1, 5});
}

void Game::mateIn6(Board& board){
    board.board[1][4] = Helper::createBishop(Color::WHITE, {0, 4});
    board.board[1][5] = Helper::createKing(Color::WHITE, {0, 5});
    board.board[5][3] = Helper::createBishop(Color::WHITE, {5, 3});

    board.board[3][7] = Helper::createKing(Color::BLACK, {3, 7});
}

void Game::startGame(){
    Board board;
    initialBoard(board);
    board.prepareMoves();
    board.printBoard();

    int c = 1;
    cout<<"0 Print valid moves for specific Piece"<<endl;
    cout<<"1 The engine will play white move"<<endl;
    cout<<"2 The engine will play black move"<<endl;
    cout<<"3 Play a move manually"<<endl;

    chrono::duration<double> duration;
    while(cin>>c){
        pair<int, int> from, to;
        pair<pair<int, int>, pair<pair<int, int>, int>> ret;
        Engine::maxDepth = 4;

        if(c == 0){// Print valid moves for specific Piece
            cout<<"Enter the position of the piece: ";
            cin>>from.first>>from.second;
            for(auto&i:board.board[from.first][from.second]->moves)
                cout<<i.first<<i.second<<" ";cout<<endl;
            continue;
        }else if(c == 1){// white move
            Engine::maxDepth = 2;
            int movesCnt = 0;
            while(Engine::maxDepth<6||duration.count()*movesCnt<=100){
                if(Engine::maxDepth!=2)
                    cout<<"Calculating..., Depth : "<<Engine::maxDepth<<",Expected Time : "<<duration.count()*movesCnt<<" Seconds"<<endl;
                
                int oldDepth = Engine::maxDepth;
                auto start = chrono::high_resolution_clock::now();

                ret = Engine::getMove(board, Color::WHITE);
                auto end = chrono::high_resolution_clock::now();
                duration = chrono::duration_cast<chrono::microseconds>(end - start);
                vector<pair<int, pair<pair<int, int>, pair<int, int>>>> moves(Engine::maxValidMovesInChess);
                int blackSize = 0, whiteSize = 0;
                Helper::generateMoves(board, Color::BLACK, moves, blackSize, 1, 0, 0);
                Helper::generateMoves(board, Color::WHITE, moves, whiteSize, 1, 0, 0);
                movesCnt = max(blackSize, whiteSize);
                Engine::maxDepth = oldDepth + 2;
            }
            if(ret.second.first.first == KING_SIDE_CASLE||ret.second.first.first==QUEEN_SIDE_CASLE)
                Helper::playMove(board,Color::WHITE, ret.first, ret.second.first, nullptr, nullptr);
            else if(ret.first.first != -1)
                Helper::playMove(board, Color::WHITE, ret.first, ret.second.first, board.board[ret.first.first][ret.first.second], nullptr);
            else{
                cout<<"StaleMate"<<endl;
                return;
            }
        }else if(c == 2){// black move
            Engine::maxDepth = 2;
            int movesCnt = 0;
            while(Engine::maxDepth<6||duration.count()*movesCnt<=100){
                if(Engine::maxDepth!=2)
                    cout<<"Calculating..., Depth : "<<Engine::maxDepth<<",Expected Time : "<<duration.count()*movesCnt<<" Seconds"<<endl;

                int oldDepth = Engine::maxDepth;
                auto start = chrono::high_resolution_clock::now();

                ret = Engine::getMove(board, Color::BLACK);
                auto end = chrono::high_resolution_clock::now();
                duration = chrono::duration_cast<chrono::microseconds>(end - start);
                vector<pair<int, pair<pair<int, int>, pair<int, int>>>> moves(Engine::maxValidMovesInChess);
                int blackSize = 0, whiteSize = 0;
                Helper::generateMoves(board, Color::BLACK, moves, blackSize, 1, 0, 0);
                Helper::generateMoves(board, Color::WHITE, moves, whiteSize, 1, 0, 0);
                movesCnt = max(blackSize, whiteSize);
                Engine::maxDepth = oldDepth + 2;
            }
            if(ret.second.first.first == KING_SIDE_CASLE||ret.second.first.first==QUEEN_SIDE_CASLE)
                 Helper::playMove(board,Color::BLACK, ret.first, ret.second.first, nullptr, nullptr);
            else if(ret.first.first != -1)
                Helper::playMove(board, Color::BLACK, ret.first, ret.second.first, board.board[ret.first.first][ret.first.second], nullptr);
            else{
                cout<<"No moves"<<endl;
                return;
            }
        }else{// Play a move manually 
            cout<<"Enter the from and to positions: ";
            string stringMove;
            cin>>stringMove;

            auto move = Helper::decodeMove(stringMove);
            from = move.first;
            to = move.second;
                

            Helper::playMove(board, board.board[from.first][from.second]->color, from, to, board.board[from.first][from.second], nullptr);
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
    chrono::duration<double> duration;
    chrono::duration<double> maxi;
    board.printBoard();
    while(1){
        auto start = chrono::high_resolution_clock::now();
        auto move = Engine::getMove(board, turn?Color::WHITE:Color::BLACK);
        auto end = chrono::high_resolution_clock::now();
        auto cur = chrono::duration_cast<chrono::seconds>(end - start);
        duration += cur;
        if(cur.count() > maxi.count()) maxi = cur;
        
        if(move.second.first.first == KING_SIDE_CASLE||move.second.first.first==QUEEN_SIDE_CASLE)
            Helper::playMove(board,turn?Color::WHITE:Color::BLACK, move.first, move.second.first, nullptr, nullptr);
        else if(move.first.first != -1)
            Helper::playMove(board, turn?Color::WHITE:Color::BLACK, move.first, move.second.first, board.board[move.first.first][move.first.second], nullptr);
        else{
            cout<<"StaleMate"<<endl;
            return;
        }
        board.printBoard();
        cout<<"Cur move time: "<<cur.count()<<endl;
        cout<<"Max move time: "<<maxi.count()<<endl;
        cout<<"Total time: "<<duration.count()<<endl;
        cnt++;
        turn = !turn;
    }
}
