#include "Board/Board.h"
#include "Engine/Engine.h"
#include "Helper/Helper.h"
#include "Board/Pieces/Headers/King.h"
#include "Board/Pieces/Headers/Rook.h"
#include <iostream>

using namespace std;

class Game{
    public:
    void startGame();
};

void Game::startGame(){
    // Initialize the game
    Board board;
    board.initializeBoard();
    
    board.board[5][2] = board.board[3][0];
    board.board[3][0] = nullptr;
    board.board[5][2]->position = {5, 2};

    board.board[2][3] = board.board[5][0];
    board.board[5][0] = nullptr;
    board.board[2][3]->position = {2, 3};

    board.board[4][6] = nullptr;

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
                auto ret = Engine::getMove(board, Color::WHITE, 0);
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